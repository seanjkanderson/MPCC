function [state_pred, input_pred, sol, exitflag, CMPC] = cautiousMPCController(stage, gp, mpc_vars, ModelParams, previous_x, learned)

tic;
% initialize variables
nx = ModelParams.nx;
nu = ModelParams.nu;
x = sdpvar(nx+nu,mpc_vars.N+1);
u = sdpvar(nu,mpc_vars.N);
sigma = sdpvar(nx+nu, nx+nu, mpc_vars.N);

% initial conditions
objective = 0;
constraints = [x(:,1) == blkdiag(mpc_vars.Tx,mpc_vars.Tu)*[stage(1).x0;stage(1).u0]];
sigma(:, :, 1) = zeros(nx+nu, nx+nu);

for k = 1:mpc_vars.N
    % Introduce stage cost: let cost(mu_ix, mu_iu, sigma_ix)
    objective = objective + 0.5*(x(:,k)'*stage(k).Qk*x(:,k) + ...
    u(:,k)'*stage(k).Rk*u(:,k)) + stage(k).fk'*x(:,k); 
    
    % Add the dynamical constraint on x
    % TODO: figure out how to actually use GP here
    if learned
        constraints = [constraints,
            x(:,k+1) == stage(k).Ak*x(:,k) + stage(k).Bk*u(:,k) + stage(k).gk 
            + mpc_vars.Bd * stage(k).muD; % add the dynamical constraint
            ];
    else
        % for the first lap, use nominal model
        constraints = [constraints,
        x(:,k+1) == stage(k).Ak*x(:,k) + stage(k).Bk*u(:,k) + stage(k).gk];

    end
    
    constraints = [constraints;
                   stage(k).lb <= [x(:,k);u(:,k)] <= stage(k).ub; % bounds
                   stage(k).lg <= stage(k).Ck'*x(:,k) <= stage(k).ug;
%                      stage(k).lb(1:nx) <= x(:,k) <= stage(k).ub(1:nx); % bounds
%                      stage(k).lb(end-nu+1:end) <= u(:,k) <= stage(k).ub(end-nu+1:end); % bounds
%                    norm(x(1:2,k) - stage(k).Ck_new, 2) <= stage(k).dk %track constraints
%                     -stage(k).Ck'*x(:,k) <= stage(k).lg;
%                     stage(k).Ck'*x(:,k) <= stage(k).ug;
                   ]; 
   
end
% Add terminal cost: let terminal_cost = f(mu_ix, mu_iu, sigma_ix)
k = mpc_vars.N+1;
objective = objective + 0.5*(x(:,k)'*stage(k).Qk*x(:,k)) + stage(k).fk'*x(:,k);
% Add terminal constraints
constraints = [constraints;
               stage(k).lb(1:nx+nu) <= x(:,k) <= stage(k).ub(1:nx+nu); %bounds
%                 norm(x(1:2,k) - stage(k).Ck_new, 2) <= stage(k).dk % track constraints
                stage(k).lg <= stage(k).Ck'*x(:,k) <= stage(k).ug;
               ];  

options = sdpsettings('verbose', 1, 'solver', 'gurobi');
toc;
% if previous_x
%     assign(x(1:nx,:), previous_x);
%     options = sdpsettings(options, 'usex0',1);    
% end
% options.gurobi.BarHomogeneous = 1;
% TODO: switch to optimizer() when problem is stable
sol = optimize(constraints, objective, options);
toc;

exitflag = sol.problem;
if exitflag == 0
    input_pred = mpc_vars.invTu*value(x(nx+1:end,2:end));
    state_pred = mpc_vars.invTx*value(x(1:nx,:));
    
else
    % Improve printout
    disp(sol);
end
end

