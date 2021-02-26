function [state_pred, input_pred, dU, sol, exitflag] = cautiousMPCControllerFORCESNLP(cons, gp, mpc_vars, ModelParams, previous_x, learned)

tic;
% initialize variables
nx = ModelParams.nx;
nu = ModelParams.nu;
% change nx to be nx+nu for clarity in the code. A and B are already super
% matrices that encode the input rate constraint!
nx_orig = nx;
nx = nx + nu;
N = mpc_vars.N;

i = 1; %TODO: not sure how to make this TV?
if mpc_vars.reformulate
    model.N     = N;   % horizon length
    model.nvar  = nx+nu;    % number of variables
    model.neq   = nx+nu;    % number of equality constraints
    model.npar = 0; % number of runtime parameters
    model.continuous_dynamics = @fx_bicycle;
    
    % Indices on LHS of dynamical constraint - for efficiency reasons, make
    % sure the matrix E has structure [0 I] where I is the identity matrix.
    model.E = [zeros(nx,nu), eye(nx)];
    
    % upper/lower variable bounds lb <= x <= ub
    model.lb = cons(i).lb;
    model.ub = cons(i).ub;

    % objective 
    model.objective = @(z) z(1)*R*z(1) + [z(2);z(3)]'*Q*[z(2);z(3)];
    model.objectiveN = @(z) z(1)*R*z(1) + [z(2);z(3)]'*P*[z(2);z(3)];

    % equalities
    model.eq = @(z) [ A(1,:)*[z(2);z(3)] + B(1)*z(1);
                      A(2,:)*[z(2);z(3)] + B(2)*z(1)];

    model.E = [zeros(2,1), eye(2)];

    % initial state
    model.xinitidx = 2:3;

    % inequalities
    model.lb = [ umin,    xmin  ];
    model.ub = [ umax,    xmax  ];


    %% Generate FORCESPRO solver

    % get options
    codeoptions = getOptions('CMPCNLPsolver');
    codeoptions.maxit = 200;
    codeoptions.printlevel = 2;
    codeoptions.optlevel = 3;
    codeoptions.nlp.integrator.Ts = integrator_stepsize; 
    codeoptions.nlp.integrator.nodes = 5; 
    codeoptions.nlp.integrator.type = 'ERK4';
    codeoptions.solvemethod = 'SQP_NLP';
    codeoptions.nlp.hessian_approximation = 'gauss-newton';
    codeoptions.sqp_nlp.use_line_search = 0;
    codeoptions.nlp.ad_tool = 'casadi-3.5.1';
    
    %codeoptions.nlp.ad_tool = 'symbolic-math-tbx';

    % generate code
    FORCES_NLP(model, codeoptions);

    stages = MultistageProblem(N+1); % get stages struct of length N
    % z_i = [u_i; x_i1];

    for i = 1:N+1

        % dimension 
        stages(i).dims.n = nx+nu;     % number of stage variables
        stages(i).dims.r = nx;        % number of equality constraints
        stages(i).dims.p = 2;           % number of polytopic constraints
        stages(i).dims.q = 0;            % number of quadratic constraints

        if i > N
            idx = 1:nx;
        else
            idx = 1:nx+nu;
        end

        stages(i).dims.l = length(idx);            % number of lower bounds
        stages(i).dims.u = length(idx);            % number of upper bounds

        % lower 
        stages(i).ineq.b.lbidx = idx;  
        stages(i).ineq.b.lb = cons(i).lb(idx);    

        % upper 
        stages(i).ineq.b.ubidx = idx;  
        stages(i).ineq.b.ub = cons(i).ub(idx); 

        if i < N + 1
            stages(i).dims.r = nx;        % number of equality constraints
            params(i+1) = newParam(append('equality',num2str(i)),i,'eq.C');
            params(N+1+i) = newParam(append('equality_rhs',num2str(i)),i+1,'eq.c');
        end

        % cost
        params(2*N+1+i) = newParam(append('cost_H', num2str(i)),i,'cost.H');
        params(3*N+2+i) = newParam(append('cost_f', num2str(i)),i,'cost.f');

        params(4*N+3+i) = newParam(append('eq_D', num2str(i)),i, 'eq.D');

        % polytopic
        params(5*N+4+i) = newParam(append('polytopic_A', num2str(i)),i,'ineq.p.A');
        params(6*N+5+i) = newParam(append('polytopic_b', num2str(i)),i,'ineq.p.b');
%         stages(i).ineq.q.idx = {[1 2]};
%         params(5*N+4+i) = newParam(append('quad_Q', num2str(i)),i,'ineq.q.Q');
%         params(6*N+5+i) = newParam(append('quad_L', num2str(i)),i,'ineq.q.l');
%         params(7*N+6+i) = newParam(append('quad_r', num2str(i)),i,'ineq.q.r');
        
    end 

    params(1) = newParam('minusA_times_x0',1,'eq.c');

    % Outputs
    outputs(1) = newOutput('z',1:N+1,1:nx+nu);

    codeoptions = getOptions('FORCES_CMPC');


    %% Generate code
    generateCode(stages,params,codeoptions,outputs);
end

%% Solve the problem
problem.minusA_times_x0 = -blkdiag(mpc_vars.Tx,mpc_vars.Tu)*[cons(1).x0;cons(1).u0];
problem.C1 = zeros(nx);
for i=1:N+1
    i_str = num2str(i);
    
    % cost
    if i < N + 1
        problem.(append('cost_H',i_str)) = blkdiag(cons(i).Qk, cons(i).Rk);
    else
        problem.(append('cost_H',i_str)) = blkdiag(cons(i).Qk, zeros(3));
    end
    problem.(append('cost_f',i_str)) = [cons(i).fk; zeros(nu,1)];
    
    % equality constraints
    if i < N+1
        problem.(append('equality',i_str)) = [cons(i).Ak, zeros(nx,nu)];
    end
    
    if learned
        try
            aux = cons(i).gk + blkdiag(mpc_vars.Tx,eye(3)) * [mpc_vars.Bd * cons(i).muD; zeros(4,1)];
        catch
            aux = [];
        end
    else
        try
            aux = cons(i).gk + [-0.0047*ones(6,1);zeros(4,1)];
        catch
            aux = [];
        end
    end
    
    problem.(append('equality_rhs',i_str)) = - aux; 
    
    % polytopic constraints
    problem.(append('polytopic_A',i_str)) = [cons(i).Ck', zeros(1,nu); -cons(i).Ck', zeros(1,nu)]; %
    problem.(append('polytopic_b',i_str)) = [cons(i).ug; cons(i).lg]; %
    
%     problem.(append('quad_Q',i_str)) = cons(i).Q;
%     problem.(append('quad_L',i_str)) = cons(i).L;
%     problem.(append('quad_r',i_str)) = cons(i).r;
    
    if i > 1
        problem.(append('eq_D',i_str)) = [-eye(nx) cons(i-1).Bk];
    else
        problem.(append('eq_D',i_str)) = [-eye(nx) zeros(nx,3)];
    end
%     problem.(append('eq_D',i_str)) = [-eye(nx) cons(1).Bk];
    
end

start = tic;
[sol, exitflag] = FORCES_CMPC(problem);
elapsed = toc;

output = reshape(sol.z,nx+nu,N+1);
sol = struct;
sol.time = elapsed;
% Now work with the original nx to extract the output!
if exitflag == 1
    input_pred = mpc_vars.invTu*value(output(nx_orig+1:nx_orig+nu,2:end));
    state_pred = mpc_vars.invTx*value(output(1:nx_orig,:));
    dU = value(output(nx+1:end,2:end));
    exitflag = 0;
else
    % Improve printout
    disp(output);
    exitflag = 1;
    input_pred = [];
    state_pred = [];
    dU = [];
end
end