clc;
rng('default') % For reproducibility
x1 = linspace(0,10,21);
x2 = linspace(2,10,21);
x_observed = [x1;x2];
u_observed = linspace(5,10,21);
y_observed = x_observed.*sin(x_observed) + 0.5*randn(size(x_observed));

%% Test the MATLAB GP
tic;
gprMdl2a = fitrgp([x_observed; u_observed]',y_observed(1,:),'OptimizeHyperparameters','auto','HyperparameterOptimizationOptions',...
    struct('AcquisitionFunctionName','expected-improvement-plus'));
kfcn = gprMdl2a.Impl.Kernel.makeKernelAsFunctionOfXNXM(gprMdl2a.Impl.ThetaHat);
gprMdl2b = fitrgp([x_observed; u_observed]',y_observed(2,:),'OptimizeHyperparameters','auto','HyperparameterOptimizationOptions',...
    struct('AcquisitionFunctionName','expected-improvement-plus'));
toc

kfcn2a = gprMdl2a.Impl.Kernel.makeKernelAsFunctionOfXNXM(gprMdl2a.Impl.ThetaHat);
kfcn2b = gprMdl2b.Impl.Kernel.makeKernelAsFunctionOfXNXM(gprMdl2b.Impl.ThetaHat);
% gram_input = obj.computeGram(z_input, obj.z, i);
%                 gram_in_in = obj.computeGram(z_input, z_input, i);
%                 sigma(i) = gram_in_in * -gram_input * obj.inv_gram_y(i) * gram_input';
% mu_2a = @(x1,x2) kfcn2a(x1,x1) - kfcn2a(x1,x2) *

%% Test the custom GP
tic;
L_a = {gprMdl2a.KernelInformation.KernelParameters(1:end-1), gprMdl2b.KernelInformation.KernelParameters(1:end-1)};
sigma_f = [gprMdl2a.KernelInformation.KernelParameters(end), gprMdl2b.KernelInformation.KernelParameters(end)];
measurement_noise = [gprMdl2a.Sigma, gprMdl2b.Sigma];
gprMdl1 = GaussianProcess(false, measurement_noise, L_a, sigma_f);
gprMdl1 = gprMdl1.fitGP(x_observed, u_observed, y_observed);
toc


%% Plot
x1 = linspace(0,10);
x2 = linspace(2,10);
x = [x1;x2];
u = linspace(5,10);
ypred1 = gprMdl1.muD(x,u);

[ypred2a,~,~] = predict(gprMdl2a,[x;u]');
[ypred2b,~,~] = predict(gprMdl2b,[x;u]');
ypred2 = [ypred2a';ypred2b'];

fig = figure;
fig.Position(3) = fig.Position(3)*2;

tiledlayout(1,2,'TileSpacing','compact')

nexttile
hold on
scatter(x_observed(1,:),y_observed(1,:),'r') % Observed data points
fplot(@(x) x.*sin(x),[0,10],'--r')  % Function plot of x*sin(x)
plot(x(1,:),ypred1(1,:),'g')                  % GPR predictions
% patch([x;flipud(x)],[yint1(:,1);flipud(yint1(:,2))],'k','FaceAlpha',0.1); % Prediction intervals
hold off
title('GPR Fit of Noisy Data - Custom (SA) GP')
legend({'Noisy observations','g(x) = x*sin(x)','GPR predictions'},'Location','best')

nexttile
hold on
scatter(x_observed(1,:),y_observed(1,:),'xr') % Observed data points
fplot(@(x) x.*sin(x),[0,10],'--r')   % Function plot of x*sin(x)
plot(x(1,:),ypred2(1,:),'g')                   % GPR predictions
% patch([x;flipud(x)],[yint2(:,1);flipud(yint2(:,2))],'k','FaceAlpha',0.1); % Prediction intervals
hold off
title('GPR Fit of Noisy Data - vMATLAB')
legend({'Noisy observations','g(x) = x*sin(x)','GPR predictions'},'Location','best')