% Copyright (C) 2018, ETH Zurich, D-ITET, Kenneth Kuchera, Alexander Liniger
% Licensed under the Apache License, Version 2.0 (the "License");
% you may not use this file except in compliance with the License.
% You may obtain a copy of the License at
% 
%     http://www.apache.org/licenses/LICENSE-2.0
% 
% Unless required by applicable law or agreed to in writing, software
% distributed under the License is distributed on an "AS IS" BASIS,
% WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
% See the License for the specific language governing permissions and
% limitations under the License.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [X,U,dU,gp,info, exitflag, solver, stage] = dataPrep(traj, MPC_vars,ModelParams,borders,X_pred, U_pred, X_hist, U_hist, dU_hist,gp, x0,u0, previous_soln, controller_name)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% For each stage in the horizon compute the necessary system and cost %%%%%
% matricies and safe them in a array of structs 'stage' %%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% cost scaling for numerics
costScale = MPC_vars.costScale;
% init stage struct
stage = struct([]);
%% Generate MPC problem

if MPC_vars.learned && ~isa(gp,'GaussianProcess')
    gp = fitGP(X_hist, U_hist, MPC_vars, ModelParams);
end

stage(1).x0 = x0;
stage(1).u0 = u0;
%covariance matrix starts out as 0 since state is known.
% sigma = zeros(ModelParams.nx-1);
effective_borders = [];
for i = 1:MPC_vars.N
     Xk = X_pred(:,i);
     Uk = U_pred(:,i);
    % generate quadratic state(-input) cost
    stage(i).Qk = costScale*generateH(traj,MPC_vars,ModelParams,Xk,i);

    % quadratic rate input cost 
    stage(i).Rk = costScale*2*diag([MPC_vars.rdD; MPC_vars.rdDelta; MPC_vars.rdVtheta]);
    % linear state(-input) cost
    stage(i).fk = costScale*generatef(traj,MPC_vars,ModelParams,Xk,i);
    % posterior prediction parameterized by index
    stage(i).muD = posteriorPrediction(Xk, Uk, MPC_vars.Tx, gp);
    % linearized dynamics
    [stage(i).Ak,stage(i).Bk,stage(i).gk] = getEqualityConstraints(Xk,Uk,MPC_vars,ModelParams);
    % linearized track constraints
    [stage(i).Ck, stage(i).ug, stage(i).lg, e_border] = getInequalityConstraints(borders(max(i-1,1),:),MPC_vars,ModelParams, MPC_vars,gp,Xk,Uk,i);
    % track constraints: formulate the probabilistic inequality constraints
    % TODO: bad practice to only pass index for some variables (SA)
    [stage(i).Q, stage(i).L, stage(i).r, ~] = getProbInequalityConstraints(borders(max(i-1,1),:),MPC_vars,[], Xk,Uk,gp,ModelParams, i);
    % bounds
    [stage(i).lb, stage(i).ub] = getBounds(MPC_vars,ModelParams);
    effective_borders = [effective_borders; e_border];
end
% terminal stage
i = MPC_vars.N+1; 
Xk = X_pred(:,i);
% generate quadratic state(-input) cost
stage(i).Qk = costScale*generateH(traj,MPC_vars,ModelParams,Xk,i);
% quadratic rate input cost 
stage(i).Rk = costScale*2*diag([MPC_vars.rdD; MPC_vars.rdDelta; MPC_vars.rdVtheta]);
% linear state(-input) cost
stage(i).fk = costScale*generatef(traj,MPC_vars,ModelParams,Xk,i);
% posterior prediction parameterized by index
stage(i).muD = posteriorPrediction(Xk, Uk, MPC_vars.Tx, gp);
% linearized track constraints
[stage(i).Ck, stage(i).ug, stage(i).lg, e_border] = getInequalityConstraints(borders(i-1,:),MPC_vars,ModelParams,MPC_vars,gp, Xk,Uk,i);
[stage(i).Q, stage(i).L, stage(i).r, ~] = getProbInequalityConstraints(borders(max(i-1,1),:),MPC_vars,[], Xk,Uk,gp,ModelParams, i);
% bounds
[stage(i).lb, stage(i).ub] = getBounds(MPC_vars,ModelParams);

effective_borders = [effective_borders; e_border];
% figure(1); hold on; plot(effective_borders(:,1),effective_borders(:,2),'rx');
% plot(effective_borders(:,3),effective_borders(:,4),'bx');
% figure(2); plot(stage(1).x0(1),stage(1).x0(2),'bo');
% track_constraints = [];
% for i=1:MPC_vars.N+1
%     track_constraints
% end
% figure(1); plot(borders(:,1),borders(:,2),'k.'); plot(borders(:,3),borders(:,4),'k.');
%% Call solver interface
if strcmp(controller_name, 'cmpc')
    % yalmip based interface (very slow)
    [X,U,info, exitflag] = cautiousMPCController(stage, gp, MPC_vars, ModelParams, previous_soln, MPC_vars.learned);
    solver = struct;
elseif strcmp(controller_name, 'cmpc_linear')
    % yalmip based interface (very slow)
    [X,U,info, exitflag, solver] = cautiousMPCControllerLinear(stage, gp, MPC_vars, ModelParams, previous_soln, MPC_vars.learned);
elseif strcmp(controller_name, 'cmpc_forces')
    [X, U, dU, info, exitflag] = cautiousMPCControllerFORCES(stage, gp, MPC_vars, ModelParams, previous_soln, MPC_vars.learned);
    solver = struct;
elseif strcmp(controller_name, 'cmpc_dummy')
    % yalmip based interface (very slow)
    [X,U,info, exitflag] = cautiousMPCControllerDummy(stage, gp, MPC_vars, ModelParams, previous_soln, MPC_vars.learned);
else
    error('invalid optimization interface')
end

end

function muD = posteriorPrediction(x, u, tx, gp)
    
    try
        muD = tx(1:6,1:6) * gp.muD(x(1:6), u);
    catch
        muD = NaN;
    end
end

function gprMdl = fitGP(x, u, mpc_vars, ModelParams)
    nx = size(x,1);
%     gp = struct;
    x_k1 = x(1:end-1, 2:end);
    
    x = x(:, 1:end-1);
    u = u(:, 1:end-1);
    
    if ModelParams.simple_linear
        xk1_pred = [];
        for i=1:length(x)
            [A,B,~] = DiscretizedLinearizedModel(x(:,i),u(:,i),ModelParams,mpc_vars.Ts);
            xk1_pred = [xk1_pred, A(1:end-1,1:end-1)*x(:,i) + B(1:end-1,:)*u(:,i)];
        end
        y = pinv(mpc_vars.Bd)*(x_k1 - xk1_pred);
    else
        x_pred = mpc_dynamics(-1, x, u, @fx_bicycle, ModelParams, mpc_vars.Ts, true);
        dx = x - x_pred;
        x = x(1:end-1,:); % get rid of counter state for now
        % TODO: not sure if should not include the distance travelled state.
        y = pinv(mpc_vars.Bd)*(dx(1:6,:));
    end
        
    % TODO: sparse GP?
%         gp.model(i) = fitrgp(x, y, 'KernelFunction', 'squaredexponential',...
%           'PredictMethod','fic');
    % TODO: use the MATLAB GP since it uses efficient bayesian optimization
    % for the hyperparameter search. Extract these and use them in
    % home-cooked GP. This does not use GP from MATLAB because extracting
    % the posterior covariance is not trivial. But I think it can be
    % constructed using:
    % kfcn2b = gprMdl2b.Impl.Kernel.makeKernelAsFunctionOfXNXM(gprMdl2b.Impl.ThetaHat);
    % which gives you the kernel function that can be evaluated to find
    % Sigma.
    if  ModelParams.train
        cv = cvpartition(size(x,2),'HoldOut',0.2);
        idx = cv.test;
        % Separate to training and test data
        [sigma_w, L_a, sigma_f] = fitMATLABGP(x(:,~idx),u(:,~idx), y(:,~idx));
        gprMdl = GaussianProcess(false, sigma_w, L_a, sigma_f);
        gprMdl = gprMdl.fitGP(x(:,~idx),u(:,~idx), y(:,~idx));
        save('GP_params','sigma_w','L_a', 'sigma_f','gprMdl');
        
        x_pred_hat = mpc_vars.Bd * gprMdl.muD(x(:,idx),u(:,idx)) + x_pred(1:nx-1,idx);
        x_pred_hat_train = mpc_vars.Bd * gprMdl.muD(x(:,~idx),u(:,~idx)) + x_pred(1:nx-1,~idx);
        
        f = figure(4); clf; 
        for i = 1:6
            rmse = sqrt(mean((x(i,idx)-x_pred_hat(i,:)).^2)) / mean(x(i,idx));
            rmse_train = sqrt(mean((x(i,~idx)-x_pred_hat_train(i,:)).^2)) / mean(x(i,~idx));
            subplot(3,2,i); hold on; 
            yyaxis left
            plot(x(i,idx)-x_pred(i,idx),'b-.');
            ylabel('Nominal pred. error');
            yyaxis right;
            plot(x(i,idx)-x_pred_hat(i,:),'r-o'); 
            
            legend('GP Prediction','Nominal prediction');
            title(['Test set residuals (state ', num2str(i), ') | Test nRMSE:', num2str(rmse,'%.3e'), ' | Train nRMSE: ', num2str(rmse_train,'%.3e')]);
            xlabel('Sample (index)'); ylabel('GP pred. error');
        end
        set(gcf,'Position',[0 0 1400 800]);
        saveas(f,'train_test_1','fig')
    else
        load('GP_params','gprMdl');
    end
    
end

function [sigma_w, L_a, sigma_f] = fitMATLABGP(x,u, y)
    ny = size(y,1);
    L_a = cell(ny,1);
    sigma_f = nan(ny,1);
    sigma_w = nan(ny,1);
    for i = 1:ny
        gprMdl = fitrgp([x; u]',y(i,:),'OptimizeHyperparameters','auto','HyperparameterOptimizationOptions',...
        struct('AcquisitionFunctionName','expected-improvement-plus'));
        L_a{i} = gprMdl.KernelInformation.KernelParameters(1:end-1);
        sigma_f(i) = gprMdl.KernelInformation.KernelParameters(end);
        sigma_w(i) = gprMdl.Sigma;
    end
end

% GENERATING Q
function Qk = generateH(pathinfo,MPC_vars,ModelParams,Xk,i)
    % get linearized contouring and lag errors
    Qtilde = generateQtilde(pathinfo,MPC_vars,ModelParams,Xk,i);
    % add omega regularization
    if i == MPC_vars.N+1
        Qtilde(ModelParams.stateindex_omega,ModelParams.stateindex_omega) = MPC_vars.qOmegaNmult*MPC_vars.qOmega;
    else
        Qtilde(ModelParams.stateindex_omega,ModelParams.stateindex_omega) = MPC_vars.qOmega;
    end
    % make Qtilde symetric (not symetric due to numerical issues)
    Qtilde = 0.5 *(Qtilde+Qtilde');
    % Qk = contouring-lag error and real-input cost
    Qk = 2*blkdiag(Qtilde,diag([MPC_vars.rD,MPC_vars.rDelta,MPC_vars.rVtheta]));
    % scale cost
    Qk = blkdiag(MPC_vars.invTx,MPC_vars.invTu)*Qk*blkdiag(MPC_vars.invTx,MPC_vars.invTu) + 1e-12*eye(10);
end

% compute linear contouring and lag errors
function Qtilde = generateQtilde(pathinfo,MPC_vars,ModelParams,Xk,i)
    if i == MPC_vars.N+1
        Q = diag([MPC_vars.qCNmult*MPC_vars.qC, MPC_vars.qL]);
    else
        Q = diag([MPC_vars.qC, MPC_vars.qL]);
    end
        
    theta_virt=mod(Xk(end),pathinfo.ppx.breaks(end));
    [grad_eC, grad_eL] = getErrorGradient(pathinfo, theta_virt, ModelParams,Xk(1), Xk(2));
    errorgrad = [grad_eC; grad_eL]; 
    Qtilde = errorgrad'*Q*errorgrad; 
end

function [grad_eC, grad_eL] = getErrorGradient(pathinfo, theta_virt, ModelParams, x_phys, y_phys)

    [deC_dtheta, deL_dtheta, cos_phi_virt, sin_phi_virt] = getderror_dtheta(pathinfo, theta_virt, x_phys, y_phys);
    
    grad_eC = [ sin_phi_virt, -cos_phi_virt, zeros(1, ModelParams.nx-3), deC_dtheta];
    grad_eL = [-cos_phi_virt, -sin_phi_virt, zeros(1, ModelParams.nx-3), deL_dtheta];
end

function [deC_dtheta, deL_dtheta, cos_phi_virt, sin_phi_virt] = getderror_dtheta(pathinfo, theta_virt, x_phys, y_phys)
    dxvirt_dtheta=ppval(pathinfo.dppx,theta_virt); %d x_virt / d theta
    dyvirt_dtheta=ppval(pathinfo.dppy,theta_virt); %d y_virt / d theta
    
    phi_virt=atan2(dyvirt_dtheta,dxvirt_dtheta); %orientation of virtual position
    % virtual positions
    x_virt=ppval(pathinfo.ppx,theta_virt);
    y_virt=ppval(pathinfo.ppy,theta_virt);
    
    % difference in position between virtual and physical
    Dx=x_phys-x_virt;
    Dy=y_phys-y_virt;

    dphivirt_dtheta=getdphivirt_dtheta(theta_virt,pathinfo);

    cos_phi_virt=cos(phi_virt);
    sin_phi_virt=sin(phi_virt);

    tmp1=[dphivirt_dtheta, 1];
    tmp2=[cos_phi_virt; sin_phi_virt];

    MC=[ Dx Dy; dyvirt_dtheta -dxvirt_dtheta];
    ML=[-Dy Dx; dxvirt_dtheta  dyvirt_dtheta];

    deC_dtheta = tmp1 * MC * tmp2;
    deL_dtheta = tmp1 * ML * tmp2;
end

function dphivirt_dtheta=getdphivirt_dtheta(theta_virt,pathinfo)
    % computes {d phi_virt / d theta} evaluated at theta_k

    dxdth=ppval(pathinfo.dppx,theta_virt); %d x_virt / d theta
    dydth=ppval(pathinfo.dppy,theta_virt); %d y_virt / d theta
    d2xdth2=ppval(pathinfo.ddppx,theta_virt); %d2 x_virt / d theta2
    d2ydth2=ppval(pathinfo.ddppy,theta_virt); %d2 y_virt / d theta2

    numer=dxdth*d2ydth2 - dydth*d2xdth2;
    denom=dxdth^2 + dydth^2;

    dphivirt_dtheta=numer/denom;
end

% GENERATING f
function f = generatef(pathinfo,MPC_vars,ModelParams,Xk,i)

    x_phys = Xk(1);
    y_phys = Xk(2);

    theta_virt=mod(Xk(end),pathinfo.ppx.breaks(end));
    [eC, eL] = getErrors(pathinfo, theta_virt,x_phys,y_phys);
    e=[eC;eL];
    [grad_eC, grad_eL] = getErrorGradient(pathinfo, theta_virt, ModelParams, x_phys, y_phys);
    grad_e = [grad_eC; grad_eL];
    
    if i == MPC_vars.N+1
        Q = diag([MPC_vars.qCNmult*MPC_vars.qC, MPC_vars.qL]);
    else
        Q = diag([MPC_vars.qC, MPC_vars.qL]);
    end
  
    fx=2*e'*Q*grad_e - 2*Xk'*grad_e'*Q*grad_e;
    fT = [fx, zeros(1,ModelParams.nu-1), -MPC_vars.qVtheta];
    f=fT';
    
    f = blkdiag(MPC_vars.invTx,MPC_vars.invTu)*f;
end

function [eC, eL] = getErrors(pathinfo, theta_virt,x_phys,y_phys)
    dxdth=ppval(pathinfo.dppx,theta_virt); % d x / d theta
    dydth=ppval(pathinfo.dppy,theta_virt); % d y / d theta

    % virtual positions
    x_virt=ppval(pathinfo.ppx,theta_virt);
    y_virt=ppval(pathinfo.ppy,theta_virt);
    
    phi_virt=atan2(dydth,dxdth);
    
    % define these to reduce calls to trig functions
    sin_phi_virt = sin(phi_virt);
    cos_phi_virt = cos(phi_virt);

    % contouring and lag error estimates
    eC = -sin_phi_virt*(x_virt - x_phys) + cos_phi_virt*(y_virt - y_phys);
    eL =  cos_phi_virt*(x_virt - x_phys) + sin_phi_virt*(y_virt - y_phys);
   
end

% EQUALITY CONSTRAINTS
function [Ak,Bk,gk] = getEqualityConstraints(Xk,Uk,MPC_vars,ModelParams) 

    nx = ModelParams.nx;
    nu = ModelParams.nu;
    % linearize and discretize nonlinear bicycle model
    [Ad, Bd, gd]=DiscretizedLinearizedModel(Xk,Uk,ModelParams,MPC_vars.Ts);
    % constructing augmented system with state-input scaling
    Ak = [MPC_vars.Tx*Ad*MPC_vars.invTx MPC_vars.Tx*Bd*MPC_vars.invTu; zeros(nu,nx) eye(nu)];
    Bk = [MPC_vars.Tx*Bd*MPC_vars.invTu;eye(nu)];
    gk = [MPC_vars.Tx*gd;zeros(nu,1)];
%     Ak = MPC_vars.Tx*Ad*MPC_vars.invTx;
%     Bk = MPC_vars.Tx*Bd*MPC_vars.invTu;
%     gk = MPC_vars.Tx*gd;
%     
end

function [Q, L, r, sigma] = getProbInequalityConstraints(border,MPC_vars, sigma, xk, uk, gp, ModelParams, i)
    
    % 2-norm ball formulation below
    % scale border
    nx = ModelParams.nx;
    nu = ModelParams.nu;
    xy_scale = MPC_vars.Tx(1:2,1:2);
    
    [center, r0] = getTrackDimensions(border);
    
%     figure(2); hold on; plot(center(1),center(2),'ro');
%     th = 0:pi/25:2*pi;
%     xunit = r0 * cos(th) + center(1);
%     yunit = r0 * sin(th) + center(2);
%     plot(xunit, yunit, 'magenta');
    
%     border = [border(1:2) * xy_scale, border(3:4) * xy_scale];
    [center, r0] = getTrackDimensions(border);
    center = center';
    
    try
        % TODO: gradient muD needs work on the dimensionality-side
%         A_tilde = [linearizedF(xk, uk, gp, ModelParams, MPC_vars)];
%         sigma = A_tilde * sigma * A_tilde' + ...
%             MPC_vars.Bd * gp.sigmaD(xk(1:nx-1,:),uk) * MPC_vars.Bd;
        sigma = gp.sigmaD(xk(1:nx-1,:),uk);
        deg_free = 2; % in 2d for the track constraints
        r_tightened = r0 - (chi2inv(MPC_vars.p,deg_free) * max(eig(sigma)))^.5;
    catch
        r_tightened = r0;
    end
    
    % ||x-c|| < r^2 => x'x-2c'x <= r^2 - c'c => x'*Q*x + L'x <= r
    Q = eye(2);
    L = -2*center;
    r = r_tightened^2 - center'*center;
    

end

function [center, r0] = getTrackDimensions(border)
    % Compute
    x1=border(1:2);
    x2=border(3:4);
    
    % find the center of the track at the time step
    center = (x1+x2) / 2;
    % then find the nominal radius that one must stay in (i.e. distance to
    % walls of track. Will be a quadratic inequality constraint.
    r0 = norm(x1-x2,2)/2;

end

function linF = linearizedF(x, u, gp, ModelParams, MPC_vars)
    nx = ModelParams.nx;
    linF = linearizedModel(x,u,ModelParams) + MPC_vars.Bd * gp.gradMuD(x(1:nx-1,:),u);
end
    

% INEQUALITY CONSTRAINTS
function [Ck, ug, lg, effective_border] = getInequalityConstraints(border,MPC_vars,ModelParams, mpc_vars, gp, xk, uk, i)
    nx = ModelParams.nx;
    nu = ModelParams.nu;
    x1=border(1);
    y1=border(2);
    x2=border(3);
    y2=border(4);
    
    % numerator and denominator of slope of border. m = - (x2-x1)/(y2-y1)
    numer=-(x2-x1);
    denom=(y2-y1);
    m = numer/denom;
    m_perp = -1/m;
    
%     if y1 > y2
%         x_up = x1;
%         y_up = y1;
%         x_low = x2;
%         y_low = y2;
%     elseif y1 < y2
%         x_up = x2;
%         y_up = y2;
%         x_low = x1;
%         y_low = y1;
%     elseif x1 > x2
%         x_up = x1;
%         y_up = y1;
%         x_low = x2;
%         y_low = y2;
%     else
%         x_up = x2;
%         y_up = y2;
%         x_low = x1;
%         y_low = y1;
%     end
%     
%     if x1 < x2
%         xmin = x1;
%         xmax = x2;
%     else
%         xmin = x2;
%         xmax = x1;
%     end
%     
%     a_1 = [m -1]';
%     b_1 = x_up*m - y_up;
%     a_2 = -[m -1]';
%     b_2 = -(x_low*m - y_low);
%     
%     % the Hewing paper cites only tightening for the first tH steps
%     if mpc_vars.constraint_tightening && i <= mpc_vars.tightening_horizon
%         sigma = gp.sigmaD(xk(1:nx-1,:),uk);
%         deg_free = 2;
%         b_1 = b_1 + (chi2inv(MPC_vars.p,deg_free) * sqrt(a_1'*sigma(1:2,1:2)*a_1));
%         b_2 = b_2 + (chi2inv(MPC_vars.p,deg_free) * sqrt(a_2'*sigma(1:2,1:2)*a_2));
%     end
%     
% %     x = xmin-.05:.01:xmax+.05;
% %     yup = m*x_up-b_1;
% % %     yup_mod = m*x-b_1n;
% %     ylow = m*x_low+b_2;
% %     ylow_mod = m*x+b_2n;
% %     y_perp = m_perp*(x-x1)+y1;
%     x_1 = (-m_perp * x1 + y1 - b_2)/(m-m_perp);
%     x_2 = (-m_perp * x1 + y1 + b_1)/(m-m_perp);
%     y_1 = m*x_low + b_2;
%     y_2 = m*x_up - b_1;
%     effective_border = [x_1,y_1,x_2,y_2];
%     
%     x1 = x_1;
%     x2 = x_2;
%     y1 = y_1;
%     y2 = y_2;

%     figure(4); hold on;  plot(x,yup,'r');  plot(x,ylow,'g'); plot(x_low,y_low,'kx');plot(x_up,y_up,'kx');
%     axis equal;
%     plot(x,y_perp,'bo');
%      plot(x,ylow_mod,'go'); plot(x,yup_mod,'ro');
%      plot(x1,y1,'rx'); plot(x2,y2,'rx');
    
    effective_border = [];
    dbmax=max(numer*x1-denom*y1,numer*x2-denom*y2);
    dbmin=min(numer*x1-denom*y1,numer*x2-denom*y2);

    Ck=zeros(1,nx+nu);
    Ck(1,1:2)=[numer -denom];
    ug= dbmax;
    lg= -dbmin;
    % --- 
%     m_perp = Ck(2)/Ck(1);
%     x_max = ((-m_perp*xk(1,:)+xk(2,:)) - ug/Ck(2)) / (-Ck(1)/Ck(2)-m_perp);
%     y_max = m_perp*x_max+(-m_perp*xk(1,:)+xk(2,:));
% 
%     x_min = ((-m_perp*xk(1,:)+xk(2,:)) + lg/Ck(2)) / (-Ck(1)/Ck(2)-m_perp);
%     y_min = m_perp*x_min+(-m_perp*xk(1,:)+xk(2,:));
% 
%     figure(1); hold on; plot(border(1),border(2),'go'); plot(border(3),border(4),'gx');
%     plot(x_min,y_min,'ro');plot(x_max,y_max,'rx');
    % --- 
%     ug= numer*x_up-denom*y_up;
%     lg= -(numer*x_low-denom*y_low);
    
%     if round(dbmax,3) ~= round(ug,3) || round(-dbmin,3) ~= round(lg,3)
%         error('You messed up the border calc');
%     end
    Ck = (Ck*blkdiag(MPC_vars.invTx,MPC_vars.invTu))';
    % the Hewing paper cites only tightening for the first tH steps
%     if mpc_vars.constraint_tightening && i < mpc_vars.tightening_horizon
%         deg_free = 2;
%         sigma = gp.sigmaD(xk(1:nx-1,:),uk);
%         sigma_aug = zeros(length(Ck));
%         sigma_aug(1:length(sigma),1:length(sigma)) = sigma;
%         ug_o = ug - (chi2inv(MPC_vars.p,deg_free) * sqrt(Ck'*sigma_aug*Ck));
%         % TODO: verify that this should be minus and not plus chi...
%         lg_o = lg + (chi2inv(MPC_vars.p,deg_free) * sqrt(-Ck'*sigma_aug*-Ck));
%         
%     end

    
    
    
end

% BOUNDS
function [lb, ub]=getBounds(MPC_vars,ModelParams)

lb = MPC_vars.bounds(:,1);
ub = MPC_vars.bounds(:,2);


end