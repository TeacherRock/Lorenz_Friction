clc; clear; close all;
latexArg = {'Interpreter','latex'};
legendArg = [latexArg(:)',{'FontSize'},{12}];
titleArg = [latexArg(:)', {'FontSize'},{16},{'FontWeight'},{'bold'}];

%% Auto fitting Version
FileNum = 1;
p2 = zeros(FileNum, 1);
% OL = [2];     % Omit List
% p2(OL) = NaN;
for ind=1:FileNum
  if isnan(p2(ind))
    continue;
  end
  % Read Data
%   FileName = ['data_S3_' num2str(ind) '.txt'];
  FileName = ['data_S3_0122.txt'];
  MeasuredData = load(FileName);
  Pos     = MeasuredData(:, 1);
  Vel     = MeasuredData(:, 2);
  PosCmd  = MeasuredData(:, 3);
  VelCmd  = MeasuredData(:, 4);
  TorCtrl = MeasuredData(:, 5);

  % Show Error
  PosError = PosCmd - Pos ;
  y = lowp(Vel(:,1),10,100,0.1,20,1000);
  VelError = VelCmd - y ;
  TorCtrl = lowp(TorCtrl(:,1),1,100,0.1,20,1000); % LP Filter ¶q´ú Tfb
  norm_PosError = norm(PosError) / norm(PosCmd);
  norm_VelError =  norm(VelError) / norm(VelCmd);
  fprintf(1, '%s: \n', FileName)
  fprintf(1, 'norm_PosError = %f (rad)\n', norm_PosError);
  fprintf(1, 'norm_VelError = %f (rad/s)\n\n', norm_VelError);

  % Time Settings
  samp_T = 0.001;
  tf = (size(MeasuredData, 1)-1) * samp_T;
  T = 0:samp_T:tf;

  % Calculate slope
  cut1 = 100;
  % cut2 = 2000;
  cut3 = 4000;
  f_all = fit(VelCmd(cut1:cut3),TorCtrl(cut1:cut3),'poly1');
  p2(ind) = f_all.p2;

  % Plot
  figure('Name', FileName, ...
        'NumberTitle', 'off', ...
        'WindowState','maximized')
  subplot(2,1,1)
  plot(VelCmd(cut1:cut3), TorCtrl(cut1:cut3));
  hold on
  plot(f_all, 'b-')
  legend('Fitted RHS curve', ...
        'Location','best',legendArg{:})
  xlabel('Velocity Command (rad/s)',legendArg{:})
  ylabel('Torque Control Signal ($N \cdot m$)',legendArg{:})
  grid on

  subplot(2,1,2)
  plot(VelCmd, TorCtrl);
  grid on
end
Fc = mean(p2, 'omitnan')