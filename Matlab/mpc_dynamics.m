function x_out = mpc_dynamics(k, xk,uk, f, ModelParams, step, nonaux)
    
%     f_eval = f(k, xk, uk, ModelParams);
%     if nonaux
%         f_eval = f_eval(1:end-1);
%     end
    
    x_out = [];
    for i=1:length(xk)
        [Ad, Bd, gd]=DiscretizedLinearizedModel(xk(:,i),uk(:,i),ModelParams,step);
        xk1 = Ad*xk(:,i) + Bd*uk(:,i) + gd;
        x_out = [x_out, xk1]; 
    end
    
%     % discretize the dynamics of the model using RK4
%     a1 = f(k, xk, uk, ModelParams);
%     if nonaux
%         a1 = a1(1:end-1);
%     end
%     
%     a2 = f(k + step/2, xk + step*a1/2, uk, ModelParams);
%     if nonaux
%         a2 = a2(1:end-1);
%     end
%     
%     a3 = f(k + step/2, xk + step*a2/2, uk, ModelParams);
%     if nonaux
%         a3 = a3(1:end-1);
%     end
%     
%     a4 = f(k + step, xk + step*a3, uk, ModelParams);
%     if nonaux
%         a4 = a4(1:end-1);
%     end
% 
%     xk1 = xk + (1/6) * step * (a1 + 2*a2 + 2*a3 + a4);
end