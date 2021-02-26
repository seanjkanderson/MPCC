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
%% MPCC Simulation Script
clear
close all
clc

%% add spline library
addpath('splines');

%% Add snopt license
setenv('SNOPT_LICENSE','~/Documents/MATLAB/snopt7.lic')
%% Load Parameters
CarModel = 'ORCA';
controller = 'cmpc_forces';
from_cache = false;
% CarModel = 'FullSize';

if ~from_cache
    MPC_vars = getMPC_vars(CarModel);
    ModelParams=getModelParams(MPC_vars.ModelNo);
    % choose optimization interface options: 'Yalmip','CVX','hpipm','quadprog'
    MPC_vars.interface = 'Yalmip';
    
    % Added by SA
    MPC_vars.reformulate = false; % whether to reformulate the optimization problem from FORCES
    MPC_vars.learned = false; % if we should use the learned model
    MPC_vars.constraint_tightening = false;
    MPC_vars.tightening_horizon = 15; % the horizon for the probabilistic constraints
    
    % Added by SA
    ModelParams.process_noise = [ones(3,1)*1e-3;ones(3,1)*1e-4; 0];
    ModelParams.simple_linear = false; % This realization is uncontrollable, so don't use it.
    ModelParams.train = false; % Whether to train a new GP or not

    
    if MPC_vars.learned
        load('linearModelData','X_hist','U_hist');
    end

    nx = ModelParams.nx;
    nu = ModelParams.nu;
    N = MPC_vars.N;
    Ts = MPC_vars.Ts;
    % copy ModelParams so that values can be adjusted to generate model
    % mismatch, etc. SA
    
    MPC_vars.ModelParams = ModelParams;
    MPC_vars.ModelParams.Cm1 = MPC_vars.ModelParams.Cm1 * 2;
    MPC_vars.ModelParams.Cm2 = MPC_vars.ModelParams.Cm2 * 2;
    MPC_vars.ModelParams.Cr0 = MPC_vars.ModelParams.Cr0 * 1;
    MPC_vars.ModelParams.Cr2 = MPC_vars.ModelParams.Cr2 * 1;
    %% import an plot track
    % use normal ORCA Track
    load Tracks/track2.mat
    % use RCP track
    % load Tracks/trackMobil.mat
    % track2 = trackMobil;
    % shrink track by half of the car widht plus safety margin
    % TODO implement orientation depending shrinking in the MPC constraints
    safteyScaling = 1.5;
    [track,track2] = borderAdjustment(track2,ModelParams,safteyScaling);

    trackWidth = norm(track.inner(:,1)-track.outer(:,1));
    fullWidth = norm(track2.inner(:,1)-track2.outer(:,1));
    % plot shrinked and not shrinked track 
    figure(1);
    plot(track.outer(1,:),track.outer(2,:),'r')
    hold on
    plot(track.inner(1,:),track.inner(2,:),'r')
    plot(track2.outer(1,:),track2.outer(2,:),'k')
    plot(track2.inner(1,:),track2.inner(2,:),'k')
    %% Simulation lenght and plotting
    simN = 4000;
    %0=no plots, 1=plot predictions
    plotOn = 1;
    %0=real time iteration, 1=fixed number of QP iterations, 2=fixed number of damped QP iterations
    QP_iter = 2;
    % number of cars 
    % there are two examples one with no other cars and one with 4 other cars
    % (inspired by the set up shown in the paper)
    n_cars = 1; % no other car
    % n_cars = 5; % 4 other cars
    %% Fit spline to track
    % TODO spline function only works with regular spaced points.
    % Fix add function which given any center line and bound generates equlally
    % space tracks.
    [traj, borders] =splinify(track);
    tl = traj.ppy.breaks(end);

    % store all data in one struct
    TrackMPC = struct('traj',traj,'borders',borders,'track_center',track.center,'tl',tl);
    %% Define starting position
    startIdx = 1; %point (in terms of track centerline array) allong the track 
    % where the car starts, on the center line, aligned with the track, driving
    % straight with vx0
    %since the used bicycle model is not well defined for slow velocities use vx0 > 0.5
    if CarModel == "ORCA"
        vx0 = 1;
    elseif CarModel == "FullSize"
        vx0 = 15;
    end

    % find theta that coresponds to the 10th point on the centerline
    [theta, ~] = findTheta([track.center(1,startIdx),track.center(2,startIdx)],track.center,traj.ppx.breaks,trackWidth,startIdx);

    x0 = [track.center(1,startIdx),track.center(2,startIdx),... % point on centerline
          atan2(ppval(traj.dppy,theta),ppval(traj.dppx,theta)),... % aligned with centerline
          vx0 ,0,0,theta]'; %driving straight with vx0, and correct theta progress

    % the find theta function performs a local search to find the projection of
    % the position onto the centerline, therefore, we use the start index as an
    % starting point for this local search
    last_closestIdx = startIdx;
    %% First initial guess
    x = repmat(x0,1,N+1); % all points identical to current measurment
    % first inital guess, all points on centerline aligned with centerline
    % spaced as the car would drive with vx0
    for i = 2:N+1
        theta_next = x(ModelParams.stateindex_theta,i-1)+Ts*vx0;
        phi_next = atan2(ppval(traj.dppy,theta_next),ppval(traj.dppx,theta_next));
        % phi_next can jump by two pi, make sure there are no jumps in the
        % initial guess
        if (x(ModelParams.stateindex_phi,i-1)-phi_next) < -pi
            phi_next = phi_next-2*pi;
        end
        if (x(ModelParams.stateindex_phi,i-1)-phi_next) > pi
            phi_next = phi_next+2*pi;
        end
        x(:,i) = [ppval(traj.ppx,theta_next),ppval(traj.ppy,theta_next),... % point on centerline
                  phi_next,... % aligned with centerline
                  vx0 ,0,0,theta_next]'; %driving straight with vx0, and correct theta progress
    end

    u = zeros(3,N); % zero inputs
    uprev = zeros(3,1); % last input is zero
    %% Ohter cars
    Y = ObstacelsState(track,traj,trackWidth,n_cars);

    if size(Y,2) ~= n_cars-1
        error('n_cars and the number of obstacles in "Y" does not match')
    end
    %% Initialize logging arrays
    X_log = zeros(nx*(N+1),simN);
    U_log = zeros(3*N,simN);
    B_log = zeros(4*N,simN);
    solver_time_log = zeros(1,simN);
    %% initializtion
    % solve problem 5 times without applying input
    % inspired by sequential quadratic programming (SQP)

    % TODO: not sure if it makes sense to always include this method (SA)
    ModelParams.initialize = true;
    persist_constraint_type = MPC_vars.constraint_tightening;
    MPC_vars.constraint_tightening = false;
    gp = [];
    try
        X_hist;
    catch
        X_hist = [];
        U_hist = [];
    end
    du = [];
    for i = 1:5
        % formulate MPCC problem and solve it
        Iter_damping = 0.1; % 0 no damping
        
        
        [x_up, u_up, du, b,  gp, exitflag,info, exo, constraints] = optimizer_mpc(TrackMPC,MPC_vars, n_cars, controller, Y, x, u, X_hist, U_hist, du, x0, uprev, gp,[]);
     
        x = Iter_damping*x + (1-Iter_damping)*x_up;
        u = Iter_damping*u + (1-Iter_damping)*u_up;
        
        if strcmp(controller,'cmpc_linear')
            MPC_vars.solver = exo;
        end

        if plotOn == 1
            % plot predictions
            PlotPrediction(x,u,b,Y,track,track2,traj,MPC_vars,ModelParams,constraints)
        end
        
        ModelParams.initialize = false;
    end
   
    MPC_vars.constraint_tightening = persist_constraint_type;
    %% Simulation
    % Find out how long the track is to know when a lap is complete
    track_end_i = size(track.center,2);
    track_length = findTheta([track.center(1,track_end_i),track.center(2,track_end_i)],track.center,traj.ppx.breaks,trackWidth,track_end_i);
    
    if ~MPC_vars.learned
        
        X_hist = [];
        U_hist = [];
    end
    gp = [];
    retrain = false;
    previous_soln = [];
end
if from_cache
    load('linearModelData');
%     load('linearModelAgg');
    i0 = i;
else
    i0 = 1;
    lap_count = 0;
end

for i = i0: simN
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%% MPCC-Call %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % Check to see whether GP should train (should do so after 1 lap)
    % TODO: retrain should become true again every so often (every lap?)
    if X_hist
        if last_closestIdx == 666
            lap_count  = lap_count + 1;
            if lap_count == 1
%                 save('linearModelData_26','X_hist','U_hist');
% %                 save('linearModelData');
%                 load('linearModelAgg');
%                 X_hist = X_hist_total;
%                 U_hist = U_hist_total;
                MPC_vars.learned = true;
                MPC_vars.constraint_tightening = true;
                MPC_vars.ModelParams.train = false;
            end
        end
        
        if lap_count == 1
            % Reduce chi2inv for the first 20 steps after the transition as
            % it often becomes infeasible right at the transition due to
            % the conservative track constraints
            if last_closestIdx < 666 + 20
                MPC_vars.p = 0;
            else
                MPC_vars.p = MPC_vars.p_original;
            end
        end

    end
    % augment state and inputs by shifting previus optimal solution
    [x,u] = augState(x,u,x0,MPC_vars,ModelParams,tl,TrackMPC.borders);
    %  formulate MPCC problem and solve it
    total_iteration  = 0;
    if QP_iter == 0
        [x, u, du, b, gp, exitflag,info,~,~,constraints] = optimizer_mpc(TrackMPC,MPC_vars, n_cars, controller, Y, x, u, X_hist, U_hist, du, x0, uprev, gp, previous_soln);
        previous_soln = x;
        solver_time_log(i) = info.time;
    elseif QP_iter == 1
        % doing multiple "SQP" steps
        for k = 1:2
            [x, u, du, b, exitflag,info,~,~,constraints] = optimizer_mpc(TrackMPC,MPC_vars, n_cars, controller, Y, x, u, X_hist, U_hist, du, x0, uprev, gp, previous_soln);
            solver_time_log(i) = solver_time_log(i) + info.time;
            previous_soln = x;
            if exitflag ==1 && total_iteration < 5
                k = k - 1; % Keep trying to solve the loop if it's infeasible
                total_iteration = total_iteration + 5;
            end
        end
    elseif QP_iter == 2
        % doing multiple damped "SQP" steps
        for k = 1:2
            Iter_damping = 0.75; % 0 no damping
            [x_up, u_up, du, b, gp, exitflag,info,~,constraints] = optimizer_mpc(TrackMPC,MPC_vars, n_cars, controller, Y, x, u, X_hist, U_hist, du, x0, uprev, gp, previous_soln);
            x = Iter_damping*x + (1-Iter_damping)*x_up;
            u = Iter_damping*u + (1-Iter_damping)*u_up;
            solver_time_log(i) = solver_time_log(i) + info.time;
            previous_soln = x;
%             figure(4); clf;
            
            if exitflag ==1 && total_iteration < 5
                k = k - 1; % Keep trying to solve the loop if it's infeasible
                total_iteration = total_iteration + 1;
            end
        end
        
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%% simulate system %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    x0_prev = x0; % save the previous x0
    x0 = SimTimeStep(x(:,1),u(:,1),Ts,ModelParams)';
    x0 = unWrapX0(x0);
    
    % last_closestIdx is the point on the track closest to the current
    % position (SA)
    
    [ theta, last_closestIdx] = findTheta(x0,track.center,traj.ppx.breaks,trackWidth,last_closestIdx);
    
    % Check to make sure you're within the track
    violation = checkSimConstraints(x0, last_closestIdx, ModelParams, track, fullWidth);
    
    if violation
         % stop the car
%         x0 = x0_prev;
        % set the rates to 0 so that the car is stopped
%         x0(1:2) = track.center(:,last_closestIdx); % put car in center of track
%         in = track.inner(:,last_closestIdx);
%         out = track.outer(:,last_closestIdx);
%         x0(3) = atan((in(2)-out(2))/(in(1)-out(1))) - pi/2;
%         x0(4:6) = 0;
        % don't record the data for this point as it will add noise to the
        % training. 
        warning('track violation');
    else
        X_hist = [X_hist, x0];
        U_hist = [U_hist, u(:,1)];
       
    end
        
    x0(ModelParams.stateindex_theta) = theta;
    uprev = u(:,1);
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%% plotting and logging %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    if plotOn == 1
        PlotPrediction(x,u,b,Y,track,track2,traj,MPC_vars,ModelParams, constraints)
%         figure(4); clf;
%         figure(1); clf;
    end
    
    % log predictions and time
    X_log(:,i) = reshape(x,(N+1)*7,1);
    U_log(:,i) = reshape(u,(N)*3,1);
    B_log(:,i) = reshape(b,N*4,1);
    
    
end


PlotLog( X_log,U_log,Y,track,track2,simN,Ts)


%% Generating Stats
a = 1;
for i=1:simN-1
    if X_log(ModelParams.stateindex_theta,i+1) - X_log(ModelParams.stateindex_theta,i) < -0.9*tl
        LapStart(a) = i;
        a = a+1;
    end
end

if length(LapStart) > 1
    LapTime = diff(LapStart)*Ts;
else
    LapTime = NaN;
end

disp('------------------------------------')
disp(['Lap Time(s): ',num2str(LapTime)])
disp('------------------------------------')
disp(['Mean Computation Time: ',num2str(mean(solver_time_log))])
disp(['Max Computation Time: ',num2str(max(solver_time_log))])
disp(['Min Computation Time: ',num2str(min(solver_time_log))])
disp('------------------------------------')
