% X_pred = X;
% U_pred = U;
dU = dU_hist;
x_traj = [X_pred(:,1);U_pred(:,1)];
track_bounds = [];
figure(1); hold on; 
for i=1:MPC_vars.N
    X_pred = MPC_vars.Tx * X_pred;
    U_pred = MPC_vars.Tu * U_pred;
    
    Ck = stage(i).Ck'*blkdiag(MPC_vars.Tx,MPC_vars.Tu);
    
    if any(stage(i).lb(1:10) > [X_pred(:,i);U_pred(:,i)])
        i
        warning('LB error');
    end
    
    if any(stage(i).ub(1:10) < [X_pred(:,i);U_pred(:,i)])
        i
        warning('UB error');
    end
    
    if stage(i).lg > Ck(1:7)*X_pred(:,i)
        i
        warning('LG error');
    end
    
    if stage(i).ug < Ck(1:7)*X_pred(:,i)
        i
        warning('UG error');
    end
    
%     x_traj = [x_traj, blkdiag(MPC_vars.invTx,MPC_vars.invTu) * (stage(i).Ak*x_traj(:,end) + stage(i).gk + [MPC_vars.Bd * stage(i).muD; zeros(4,1)])];
if i > 1
    B = stage(i-1).Bk;
else
    B = zeros(size(stage(1).Bk));
end
%     x_traj = [x_traj, blkdiag(MPC_vars.invTx,MPC_vars.invTu) * (stage(i).Ak*blkdiag(MPC_vars.Tx,eye(3))*[x_traj(1:7,i);U_pred(:,i)] + B*dU(:,i) + stage(i).gk) ];
    x_traj = [x_traj, blkdiag(MPC_vars.invTx,MPC_vars.invTu) * (stage(i).Ak*blkdiag(MPC_vars.Tx,eye(3))*[x_traj(1:7,i);U_pred(:,i)] + B*dU(:,i) + stage(i).gk + [MPC_vars.Bd * MPC_vars.Tx(1:6,1:6) * stage(i).muD; zeros(4,1)]) ];
%     x_traj = [x_traj, blkdiag(MPC_vars.invTx,MPC_vars.invTu) * (stage(i).Ak*blkdiag(MPC_vars.Tx,MPC_vars.Tu)*[x_traj(1:7,end);zeros(3,1)])];
    
    xx =  x_traj(1:7,end);
    uu =  x_traj(8:end,end);
    ug = stage(i).ug;
    lg = stage(i).lg;
    m_perp = Ck(2)/Ck(1);
    x_max = ((-m_perp*xx(1)+xx(2)) - ug/Ck(2)) / (-Ck(1)/Ck(2)-m_perp);
    y_max = m_perp*x_max+(-m_perp*xx(1)+xx(2));

    x_min = ((-m_perp*xx(1)+xx(2)) + lg/Ck(2)) / (-Ck(1)/Ck(2)-m_perp);
    y_min = m_perp*x_min+(-m_perp*xx(1)+xx(2));
    track_bounds = [track_bounds;x_min,y_min,x_max,y_max];
    plot([track_bounds(end,1), track_bounds(end,3)],[track_bounds(end,2), track_bounds(end,4)],'b');
    
    X_pred = MPC_vars.invTx * X_pred;
    U_pred = MPC_vars.invTu * U_pred;
end

%% 
plot(x_traj(1,:),x_traj(2,:),'bo');
% plot(X(1,:),X(2,:),'g-');
plot(track_bounds(:,1),track_bounds(:,2),'ro');
plot(track_bounds(:,3),track_bounds(:,4),'ro');

% plot(track_bounds(30,1),track_bounds(30,2),'bo');
% plot(track_bounds(30,3),track_bounds(30,4),'bo');