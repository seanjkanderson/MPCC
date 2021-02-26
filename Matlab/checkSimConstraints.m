function violation = checkSimConstraints(x0, last_closestIdx, ModelParams, track, fullWidth)

    violation = true;
    check_idx = max(last_closestIdx-5:last_closestIdx+5,1);
    check_idx(check_idx - length(track.center) > 0) = check_idx(check_idx - length(track.center) > 0) - length(track.center);
    c = track.center(:,check_idx);
    corner = cell(4,1);
    corner{1} = x0(1:2) + [cos(x0(3))*ModelParams.L/2;sin(x0(3))*ModelParams.L/2] + [sin(x0(3))*ModelParams.W/2;-cos(x0(3))*ModelParams.W/2];
    corner{2} = x0(1:2) + [cos(x0(3))*ModelParams.L/2;sin(x0(3))*ModelParams.L/2] - [sin(x0(3))*ModelParams.W/2;-cos(x0(3))*ModelParams.W/2];
    corner{3} = x0(1:2) - [cos(x0(3))*ModelParams.L/2;sin(x0(3))*ModelParams.L/2] + [sin(x0(3))*ModelParams.W/2;-cos(x0(3))*ModelParams.W/2];
    corner{4} = x0(1:2) - [cos(x0(3))*ModelParams.L/2;sin(x0(3))*ModelParams.L/2] - [sin(x0(3))*ModelParams.W/2;-cos(x0(3))*ModelParams.W/2];
    % TODO: should optimize this code to not use a for loop. SA
%     memory = cell(length(check_idx),1);
    check_corners = zeros(4,1);
    for jj=1:length(check_idx)
        % generate the four
        
        for ll = 1:4
            if norm(c(:,jj) - corner{ll}) <= fullWidth/2
                check_corners(ll) = true;
            end
        end
        
        if all(check_corners)
            violation = false;
            break
        end
    end
    
    if violation
        figure(1); hold on; 
        for ll=1:length(check_idx)
            th = 0:pi/25:2*pi;
            xunit = fullWidth/2 * cos(th) + track.center(1,check_idx(ll));
            yunit = fullWidth/2 * sin(th) + track.center(2,check_idx(ll));
            plot(xunit, yunit, 'magenta');
            
        end
    end