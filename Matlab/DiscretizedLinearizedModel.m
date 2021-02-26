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

function [Ad, Bd, gd]=DiscretizedLinearizedModel(Xbar_k,Ubar_k,ModelParams,Ts)
% returns the discretized, linearized model about (Xbar_k,Ubar_k)
% s.t. x(k+1) = Ad*x(k) + Bd*u(k) + gd
%
% Ad: [nx]x[nx], Bd: [nx]x[nu], gd: [nx]x[1]

sx=ModelParams.sx-1;
su=ModelParams.su-1;
  
% moved jacobian computation to helper function SA
[Ac, Bc, f] = linearizedModel(Xbar_k,Ubar_k,ModelParams);

if ModelParams.simple_linear
    % This will be used in one-step Euler
    Ad = zeros(sx+1,sx+1);
    Bd = zeros(sx+1,su+1);
    Ad(1:sx,1:sx) = Ts * Ac;
    Bd(1:sx,1:2) = Ts * Bc;
    
    % Set the counter state, theta, after the discretization
    Ad(end, end) = 1;
    Bd(end,end) = Ts;
    gd = nan(sx+1,1);
    
else
    gc=f-Ac*Xbar_k(1:sx)-Bc*Ubar_k(1:su);

    Bc_aug=[Bc gc];

    %discretize

    % see report for proof of following method
    tmp = expm([Ac Bc_aug; zeros(su+1,sx+su+1)]*Ts);

    Ad = zeros(sx+1,sx+1);
    Bd = zeros(sx+1,su+1);
    gd = zeros(sx+1,1);
    Ad(1:sx,1:sx) =tmp(1:sx,1:sx);
    Bd(1:sx,1:su) =tmp(1:sx,sx+1:sx+su);
    gd(1:sx) =tmp(1:sx,sx+su+1);

    % following to avoid numerical errors
    Ad(end,end)=1;
    Bd(end,end)=Ts;


    % in fact, the above can be done using only the physical states/inputs, 
    % then can add    Ad(end+1,end+1)=1; Bd(end+1,end+1)=Ts; 
end
    
end