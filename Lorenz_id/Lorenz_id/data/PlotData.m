clc; clear; close all;

%% Read Data
MeasuredData = load('data_S5_10_temp.txt');
nAxis = 1;
Axis = 1;

Pos     = MeasuredData(:, 1 + Axis*0 : Axis + Axis*0);
Vel     = MeasuredData(:, 1 + Axis*1 : Axis + Axis*1);
PosCmd  = MeasuredData(:, 1 + Axis*2 : Axis + Axis*2);
VelCmd  = MeasuredData(:, 1 + Axis*3 : Axis + Axis*3);
TorCtrl = MeasuredData(:, 1 + Axis*4 : Axis + Axis*4);

%% Show Error
PosError = PosCmd - Pos;
y = lowp(Vel(:,1),10,100,0.1,20,1000);
VelError = VelCmd - y;
TorCtrl = lowp(TorCtrl(:,1),1,100,0.1,20,1000); % LP Filter ¶q´ú Tfb

norm_PosError = zeros(1, nAxis);
norm_VelError = zeros(1, nAxis);
for i=1:Axis
    norm_PosError(1,i) = norm(PosError(:,i)) / norm(PosCmd(:,i));
    norm_VelError(1,i) = norm(VelError(:,i)) / norm(VelCmd(:,i));
end
fprintf(1, 'norm_PosError = %f (rad)\n', norm_PosError);
fprintf(1, 'norm_VelError = %f (rad/s)\n', norm_VelError);

%% Time Settings
samp_T = 0.001;
tf = (size(MeasuredData, 1)-1) * samp_T;
T = 0:samp_T:tf;

%% Plot
latexArg = {'Interpreter','latex'};
legendArg = [latexArg(:)',{'FontSize'},{12}];
titleArg = [latexArg(:)', {'FontSize'},{16},{'FontWeight'},{'bold'}];

%% Fig 1
figure('WindowState','maximized')
subplot(3,1,1)
plot(T,PosCmd,'-',T,Pos,'--',T,PosError,':','LineWidth',2)
title('Pos',titleArg{:})
xlabel('Time (sec)',legendArg{:})
ylabel('Pos (rad)',legendArg{:})
legend('PosCmd','Pos','Error',legendArg{:})
grid on

subplot(3,1,2)
plot(T,VelCmd,'-',T,y,'--',T,VelError,':','LineWidth',2)
title('Vel',titleArg{:})
xlabel('Time (sec)',legendArg{:})
ylabel('Vel (rad/s)',legendArg{:})
legend('VelCmd','Vel','Error',legendArg{:})
grid on

subplot(3,1,3)
plot(T,TorCtrl,'-','LineWidth',2)
title('TorCtrl',titleArg{:})
xlabel('Time (sec)',legendArg{:})
ylabel('Tor ($N \cdot m$)',legendArg{:})
grid on

%% Fig 2
figure(2)
cut1 = 100;
cut2 = 4000;
f_up = fit(VelCmd(cut1:cut2), TorCtrl(cut1:cut2),'poly1');
Fc = (f_up.p1*0 + f_up.p2);
plot(VelCmd, TorCtrl)
hold on
plot(f_up(0:max(VelCmd)))
title('V-T plot',titleArg{:})
legend('Torque','Fitted RHS-curve',legendArg{:})
xlabel('Velocity Command (rad/s)',legendArg{:})
ylabel('Torque Control Signal ($N \cdot m$)',legendArg{:})
xlim([min(VelCmd) max(VelCmd)]);
grid on