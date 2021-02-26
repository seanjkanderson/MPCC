function [state_pred, input_pred, sol, exitflag] = cautiousMPCControllerDummy(cons, gp, mpc_vars, ModelParams, previous_x, learned)

tic;
% initialize variables
nx = ModelParams.nx;
nu = ModelParams.nu;
% change nx to be nx+nu for clarity in the code. A and B are already super
% matrices that encode the input rate constraint!
nx_orig = nx;
nx = nx + nu;
N = mpc_vars.N;

stages = MultistageProblem(N+1); % get stages struct of length N
% z_i = [u_i; x_i1];

for i = 1:N+1

    % dimension 
    stages(i).dims.n = nx+nu;     % number of stage variables
    stages(i).dims.r = nx;        % number of equality constraints
    stages(i).dims.p = 2;           % number of polytopic constraints
    
    if i > N
        idx = 1:nx;
    else
        idx = 1:nx+nu;
    end
    
    stages(i).dims.l = 0*length(idx);            % number of lower bounds
    stages(i).dims.u = 0*length(idx);            % number of upper bounds
    
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

end 

params(1) = newParam('minusA_times_x0',1,'eq.c');

% Outputs
outputs(1) = newOutput('z',1:N,1:nx+nu);

codeoptions = getOptions('FORCES_CMPC');


%% Generate code
generateCode(stages,params,codeoptions,outputs);

%% Solve the problem
problem.minusA_times_x0 = -blkdiag(mpc_vars.Tx,mpc_vars.Tu)*[cons(1).x0;cons(1).u0];
problem.C1 = zeros(nx);
for i=1:N+1
    i_str = num2str(i);
    
    % cost
    if i < N + 1
        problem.(append('cost_H',i_str)) = 0.5*blkdiag(cons(i).Qk, cons(i).Rk);
    else
        problem.(append('cost_H',i_str)) = 0.5*blkdiag(cons(i).Qk, zeros(3));
    end
    problem.(append('cost_f',i_str)) = [cons(i).fk; zeros(nu,1)];
    
    % equality constraints
    if i < N+1
        problem.(append('equality',i_str)) = [cons(i).Ak, zeros(nx,nu)];
    end
    problem.(append('equality_rhs',i_str)) = -cons(i).gk; 
    
    % polytopic constraints
    problem.(append('polytopic_A',i_str)) = [cons(i).Ck', zeros(1,nu); -cons(i).Ck', zeros(1,nu)]; %
    problem.(append('polytopic_b',i_str)) = [cons(i).ug; cons(i).lg]; %
    
    if i > 1
        problem.(append('eq_D',i_str)) = [-eye(nx) cons(i-1).Bk];
    else
        problem.(append('eq_D',i_str)) = [-eye(nx) zeros(nx,3)];
    end
%     problem.(append('eq_D',i_str)) = [-eye(nx) cons(1).Bk];
    
end

[sol, exitflag] = FORCES_CMPC(problem);

output = reshape(sol.z,nx+nu,N);
% Now work with the original nx to extract the output!
if exitflag == 1
    input_pred = mpc_vars.invTu*value(output(nx_orig+1:end,2:end));
    state_pred = mpc_vars.invTx*value(output(1:nx_orig,:));
    
else
    % Improve printout
    disp(output);
    input_pred = [];
    state_pred = [];
end
end
    
