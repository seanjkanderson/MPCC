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

function [xTemp,uTemp] = augState(x,u,x0,MPC_vars,ModelParams,tl, borders)
    
    nx = ModelParams.nx;
    nu = ModelParams.nu;
    N = MPC_vars.N;
    Ts = MPC_vars.Ts;
    indexPhi = ModelParams.stateindex_phi;
    indexTheta = ModelParams.stateindex_theta;

    xTemp = zeros(nx,N+1);
    uTemp = zeros(nu,N);
    
    xTemp(:,1) = x0;
    uTemp(:,1) = u(:,2);
    for j=2:N-1
        xTemp(:,j) = x(:,j+1);
        uTemp(:,j) = u(:,j+1);
    end
    j = N;
    xTemp(:,j) = x(:,j+1);
    uTemp(:,j) = u(:,j);
    
    j = N+1;
    % TODO: not sure that SimTimeStep makes sense in a learning
    % context. Would need to use a more primitive model (or only what has
    % been learned so far. (SA)
%     xTemp(:,j) = SimTimeStep(x(:,N+1),u(:,N),Ts,ModelParams);
    % Instead, and also to counter scenarios in which the planned path is
    % degenerate and runs perpendicular to the track tangent, try adding
    % the next state as a point assuming constant velocity from the last n
    % points and in the direction of the centerline tangent. (SA)
    theta_phys = mod(xTemp(end,N),tl); % assume theta is last state
    x1=ppval(borders.pplx,theta_phys);
    y1=ppval(borders.pply,theta_phys);
    x2=ppval(borders.pprx,theta_phys);
    y2=ppval(borders.ppry,theta_phys);
    if (x1 < x2) && (y1 > y2)
        phi = abs(atan((x1 - x2)/(y1 - y2))) + pi/2;
    elseif (x1 < x2) && (y1 < y2)
        phi = atan((y1 - y2)/(x1 - x2)) + pi;
    else
        phi = atan((y1 - y2)/(x1 - x2));
    end
    
    % add 90 degrees to phi to get the desired heading (perp to track
    % tangent)
    phi = phi - pi/2;
    ave_velocity = sqrt(xTemp(4,N)^2 + xTemp(5,N)^2); % vx and vy.
    xTemp(1:2,j) = xTemp(1:2,N) + ave_velocity * MPC_vars.Ts * [cos(phi); sin(phi)];
    xTemp(3:end,j) = xTemp(3:end,N);
    
    % TODO: these constraints are endemic to the problem and should really
    % be parameterized.
    if xTemp(indexPhi,1) - xTemp(indexPhi,2) > pi
        xTemp(indexPhi,2:end) = xTemp(indexPhi,2:end)+2*pi;
    end
    if xTemp(indexPhi,1) - xTemp(indexPhi,2) < -pi
        xTemp(indexPhi,2:end) = xTemp(indexPhi,2:end)-2*pi;
    end
    
    if xTemp(indexTheta,1) - xTemp(indexTheta,2) < -0.75*tl
        xTemp(indexTheta,2:end) = xTemp(indexTheta,2:end)-tl;
    end
    
end