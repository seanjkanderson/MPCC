load('cmpc_linear')

tic;
% initialize variables
nx = ModelParams.nx;
nu = ModelParams.nu;
N = mpc_vars.N;

z0 = [stage(1).x0;stage(1).u0];
for i=1:N+1
    if i < N+1
        Av(:,:,i) = stage(i).Ak;
        Bv(:,:,i) = stage(i).Bk;
        gv(:,i) = stage(i).gk;
        %cost
        Rv(:,:,i) = stage(i).Rk;
        
        % bounds
        lbv(:,i) = stage(i).lb;
        ubv(:,i) = stage(i).ub;
    else
        % bounds
        lbv(:,i) = zeros(nx+nu+nu,1);
        ubv(:,i) = zeros(nx+nu+nu,1);
        lbv(1:nx+nu,i) = stage(i).lb(1:nx+nu);
        ubv(1:nx+nu,i) = stage(i).ub(1:nx+nu);
    end
        %cost
        Qv(:,:,i) = stage(i).Qk;
        fv(:,i) = stage(i).fk;
        
        ugv(:,i) = stage(i).ug;
        lgv(:,i) = stage(i).lg;
        Cv(1,:,i) = stage(i).Ck;
   
end

% initial conditions
if ModelParams.initialize
    % states and inputs
    x = sdpvar(nx+nu,N+1);
    u = sdpvar(nu,N);
    s = sdpvar(1,N+1);
    % sb = sdpvar(nx+nu,N+1);
    % sigma = sdpvar(nx+nu, nx+nu, N);

    % cost
    x0 = sdpvar(nx+nu,1);
    Q = sdpvar(nx+nu,nx+nu,N+1);
    f = sdpvar(nx+nu,N+1);
    Ru = sdpvar(nu,nu,N);

    % equality
    A = sdpvar(nx+nu,nx+nu, N);
    B = sdpvar(nx+nu,nu,N);
    g = sdpvar(nx+nu,N);

    % inequality
    lb = sdpvar(nx+nu+nu,N+1);
    ub = sdpvar(nx+nu+nu,N+1);

    lg = sdpvar(1,N+1);
    ug = sdpvar(1,N+1);
    C = sdpvar(1,nx+nu,N+1);
    
%     % cost
%     Q = Qv;
%     f = fv;
%     Ru = Rv;
    
%     % equality
    A = Av;
%     B = Bv;
%     g = gv;
    
    % inequality
%     lb = lbv;
%     ub = ubv;
    
%     lg = lgv;
%     ug = ugv;
%     C = Cv;
%     
    objective = 0;
    constraints = [x(:,1) == blkdiag(mpc_vars.Tx,mpc_vars.Tu)*x0];
%     sigma(:, :, 1) = zeros(nx+nu, nx+nu);
%     track = [];
%     dyn = [];

    for k = 1:mpc_vars.N
        % Introduce stage cost: let cost(mu_ix, mu_iu, sigma_ix)
        objective = objective + 0.5*(x(:,k)'*Q(:,:,k)*x(:,k) + ...
        u(:,k)'*Ru(:,:,k)*u(:,k)) + f(:,k)'*x(:,k)  + s(k)^2*1e4;

        % Add the dynamical constraint on x
%         if learned
%             constraints = [constraints,
%                 x(:,k+1) == A(:,:,k)*x(:,k) + B(:,:,k)*u(:,k) + g(:,k)...
%                 + [mpc_vars.Bd * stage(k).muD; zeros(4,1)]; 
%                 ];
%         else
            % for the first lap, use nominal model
        constraints = [constraints,
        x(:, k+1) == A(:,:,k)*x(:,k) + B(:,:,k)*u(:,k) + g(:,k)];
%         end

        constraints = [constraints;
                       lb(:,k) <= [x(:,k);u(:,k)] <= ub(:,k); % bounds
                        lg(1,k) <= C(1,:,k)*x(:,k) + s(k) <= ug(1,k) % track
                       ]; 

    end
    % Add terminal cost: let terminal_cost = f(mu_ix, mu_iu, sigma_ix)
    k = N+1;
    objective = objective + 0.5*(x(:,k)'*Q(:,:,k)*x(:,k)) + f(:,k)'*x(:,k) + s(k)^2*1e4;
    % Add terminal constraints
    constraints = [constraints;
                   lb(1:nx+nu, k) <= x(:,k)<= ub(1:nx+nu, k); %bounds
                    lg(1,k) <= C(1,:,k)*x(:,k) + s(k) <= ug(1,k) % track
                   ];  

    options = sdpsettings('verbose', 1, 'solver', 'gurobi');
%     CMPC = optimizer(constraints, objective, options, {x0, Q,Ru,f, A, B, g, lb, ub, lg, ug, C}, {x, u});
    params = {x0,Q,Ru,f, B, g, lb, ub, lg, ug, C};
    CMPC = optimizer(constraints, objective, options, params, {x, u, s});
    toc;
else
    CMPC = mpc_vars.solver;
end

z0 = [stage(1).x0;stage(1).u0];
for i=1:N+1
    if i < N+1
        Av(:,:,i) = stage(i).Ak;
        Bv(:,:,i) = stage(i).Bk;
        gv(:,i) = stage(i).gk;
        %cost
        Rv(:,:,i) = stage(i).Rk;
        
        % bounds
        lbv(:,i) = stage(i).lb;
        ubv(:,i) = stage(i).ub;
    else
        % bounds
        lbv(:,i) = zeros(nx+nu+nu,1);
        ubv(:,i) = zeros(nx+nu+nu,1);
        lbv(1:nx+nu,i) = stage(i).lb(1:nx+nu);
        ubv(1:nx+nu,i) = stage(i).ub(1:nx+nu);
    end
        %cost
        Qv(:,:,i) = stage(i).Qk;
        fv(:,i) = stage(i).fk;
        
        ugv(:,i) = stage(i).ug;
        lgv(:,i) = stage(i).lg;
        Cv(1,:,i) = stage(i).Ck;
   
end
% sol = optimize(constraints, objective, options);
% Ordering: {x0, Q,Ru,f, A, B, g, lb, ub, lg, ug, C}
% sol = CMPC({z0; Qv; Rv; fv; Av; Bv; gv; lbv; ubv; lgv; ugv; Cv});
sol = CMPC({ z0, Qv, Rv, fv, Bv, gv, lbv, ubv, lgv, ugv, Cv});
% if previous_x
%     assign(x(1:nx,:), previous_x);
%     options = sdpsettings(options, 'usex0',1);    
% end
% options.gurobi.BarHomogeneous = 1;
x = sol{1};
u = sol{2};


input_pred = mpc_vars.invTu*x(nx+1:end,2:end);
state_pred = mpc_vars.invTx*x(1:nx,:);

figure(1); plot(state_pred(1,:),state_pred(2,:),'bx');

    
