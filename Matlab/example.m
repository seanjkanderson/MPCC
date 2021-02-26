%% Define mostly minimal reproducible variables
% initialize variables
nx = 7;
nu = 3;
N = 10;

% % initial condition
% x0_val = [-0.8457, 1.0979, -0.7854, 1.0000, 0, 0, 0, 0,0, 0]';
% 
% % x_k1 = A*xk + B*uk + g
% A_val = [1.0000         0    0.0141    0.0141    0.0104    0.0000         0    0.0008    0.0018         0;
%          0    1.0000    0.0141   -0.0141    0.0104    0.0000         0   -0.0008    0.0018         0;
%          0         0    1.0000         0    0.0316    0.0128         0         0    0.0956         0;
%          0         0         0    0.9997         0         0         0    0.1134         0         0;
%          0         0         0         0    0.4995   -0.0073         0         0    0.1499         0;
%          0         0         0         0    2.3663    0.3704         0         0    8.3846         0;
%          0         0         0         0         0         0    1.0000         0         0    0.0200;
%          0         0         0         0         0         0         0    1.0000         0         0;
%          0         0         0         0         0         0         0         0    1.0000         0;
%          0         0         0         0         0         0         0         0         0    1.0000];
% 
% B_val = [0.0008    0.0018         0
%    -0.0008    0.0018         0;
%          0    0.0956         0;
%     0.1134         0         0;
%          0    0.1499         0;
%          0    8.3846         0;
%          0         0    0.0200;
%     1.0000         0         0;
%          0    1.0000         0;
%          0         0    1.0000];
%      
% g_val = [0.0109;
%     0.0113;
%          0;
%    -0.0251;
%          0;
%          0;
%          0;
%          0;
%          0;
%          0];
% 
% % add box constraints
% lb_val = [-3.0000;
%    -3.0000;
%   -10.0000;
%    -0.1000;
%    -2.0000;
%    -7.0000;
%          0;
%    -0.1000;
%    -0.3500;
%          0;
%    -1.0000;
%    -1.0000;
%    -5.0000];
% ub_val = [3.0000;
%     3.0000;
%    10.0000;
%     4.0000;
%     2.0000;
%     7.0000;
%    30.0000;
%     1.0000;
%     0.3500;
%     5.0000;
%     1.0000;
%     1.0000;
%     5.0000];
% 
% lg_val = 0.0110;
% ug_val = 0.0894;
% C_val = [0.1978, 0.1981, 0, 0, 0, 0, 0, 0, 0, 0];
% 
% % Define costs: x'Qx + u'Ru + f'x
% Q_val = 1e3 * [ 1.0001   -0.9999         0         0         0         0   -1.4142         0         0         0;
%    -0.9999    1.0001         0         0         0         0    1.4142         0         0         0;
%          0         0    0.0000         0         0         0         0         0         0         0;
%          0         0         0    0.0000         0         0         0         0         0         0;
%          0         0         0         0    0.0000         0         0         0         0         0;
%          0         0         0         0         0    0.0000         0         0         0         0;
%    -1.4142    1.4142         0         0         0         0    2.0000         0         0         0;
%          0         0         0         0         0         0         0    0.0000         0         0;
%          0         0         0         0         0         0         0         0    0.0000         0;
%          0         0         0         0         0         0         0         0         0    0.0000];
%      
% R_val = [0.0200         0         0;
%          0    2.0000         0;
%          0         0    0.0020];
% 
% f_val = 1e3 * [1.9436;
%    -1.9437;
%          0;
%          0;
%          0;
%          0;
%    -2.7487;
%          0;
%          0;
%    -0.0000];

load('stages');
A_val = stage(1).Ak;
B_val = stage(1).Bk;
g_val = stage(1).gk;
Q_val = stage(1).Qk;
R_val = stage(1).Rk;
f_val = stage(1).fk;
lb_val = stage(1).lb;
ub_val = stage(1).ub;
ug_val = stage(1).ug;
lg_val = stage(1).lg;
C_val = stage(1).Ck;
x0_val = [stage(1).x0; stage(1).u0];

%% Define the variables
% states and inputs
x = sdpvar(nx+nu,N+1);
u = sdpvar(nu,N);

% cost
x0 = sdpvar(nx+nu,1);
Q = sdpvar(nx+nu,nx+nu);
f = sdpvar(nx+nu,1);
Ru = sdpvar(nu,nu);

% equality
A = sdpvar(nx+nu,nx+nu);
B = sdpvar(nx+nu,nu);
g = sdpvar(nx+nu,1);

% inequality
lb = sdpvar(nx+nu+nu,1);
ub = sdpvar(nx+nu+nu,1);

lg = sdpvar(1);
ug = sdpvar(1);
C = sdpvar(1,nx+nu);

%% Set the problem up using optimize()
objective = 0;
constraints = [x(:,1) == x0_val];

for k = 1:N
    % Introduce stage cost
    objective = objective + 0.5*(x(:,k)'*Q_val*x(:,k) + ...
    u(:,k)'*R_val*u(:,k)) + f_val'*x(:,k) ; 

    constraints = [constraints,
    x(:, k+1) == A_val*x(:,k) + B_val*u(:,k) + g_val]; % dynamics

    constraints = [constraints;
                   lb_val <= [x(:,k);u(:,k)] <= ub_val; % bounds
                    lg_val <= C_val*x(:,k) <= ug_val % track
                   ]; 

end
% Add terminal cost
k = N+1;
objective = objective + 0.5*(x(:,k)'*Q_val*x(:,k)) + f_val'*x(:,k);
% Add terminal constraints
constraints = [constraints;
               lb_val(1:nx+nu) <= x(:,k)<= ub_val(1:nx+nu); %bounds
                lg_val <= C_val*x(:,k) <= ug_val % track
               ];  

options = sdpsettings('verbose', 1, 'solver', 'gurobi');
sol = optimize(constraints, objective, options);

figure(1); plot(value(x(1,:)),value(x(2,:)));

%% Set up the problem where A is NOT a parameter
objective = 0;
constraints = [x(:,1) == x0];

for k = 1:N
    % Introduce stage cost
    objective = objective + 0.5*(x(:,k)'*Q*x(:,k) + ...
    u(:,k)'*Ru*u(:,k)) + f'*x(:,k) ; 

    constraints = [constraints,
    x(:, k+1) == A_val*x(:,k) + B*u(:,k) + g]; % dynamics

    constraints = [constraints;
                   lb <= [x(:,k);u(:,k)] <= ub; % bounds
                    lg <= C*x(:,k) <= ug % track
                   ]; 

end
% Add terminal cost
k = N+1;
objective = objective + 0.5*(x(:,k)'*Q*x(:,k)) + f'*x(:,k);
% Add terminal constraints
constraints = [constraints;
               lb(1:nx+nu) <= x(:,k)<= ub(1:nx+nu); %bounds
                lg <= C*x(:,k) <= ug % track
               ];  

options = sdpsettings('verbose', 1, 'solver', 'gurobi');
CMPC = optimizer(constraints, objective, options, {x0,Q,Ru,f, B, g, lb, ub, lg, ug, C}, {x, u});

sol = CMPC({x0_val, Q_val, R_val, f_val, B_val, g_val, lb_val, ub_val, lg_val, ug_val, C_val});

x = sol{1};
figure(1); plot(x(1,:),x(2,:));
%% Now set the problem up where A is a parameter
objective = 0;
constraints = [x(:,1) == x0];

for k = 1:N
    % Introduce stage cost
    objective = objective + 0.5*(x(:,k)'*Q*x(:,k) + ...
    u(:,k)'*Ru*u(:,k)) + f'*x(:,k) ; 

    constraints = [constraints,
    x(:, k+1) == A_val*x(:,k) + B*u(:,k) + g]; % dynamics

    constraints = [constraints;
                   lb <= [x(:,k);u(:,k)] <= ub; % bounds
                    lg <= C*x(:,k) <= ug % track
                   ]; 

end
% Add terminal cost
k = N+1;
objective = objective + 0.5*(x(:,k)'*Q*x(:,k)) + f'*x(:,k);
% Add terminal constraints
constraints = [constraints;
               lb(1:nx+nu) <= x(:,k)<= ub(1:nx+nu); %bounds
                lg <= C*x(:,k) <= ug % track
               ];  

options = sdpsettings('verbose', 1, 'solver', 'gurobi');
CMPC = optimizer(constraints, objective, options, {x0,Q,Ru,f, B, g, lb, ub, lg, ug, C}, {x, u});

sol = CMPC({x0_val, Q_val, R_val, f_val, B_val, g_val, lb_val, ub_val, lg_val, ug_val, C_val});

x = sol{1};
figure(1); plot(x(1,:),x(2,:));
