clc; clear; close

%% Create Curve
Tk = [2 6 8 10];    % Design of specific time point
sampT = 0.001;      % Sampling time
T = 0:sampT:Tk(end);

% Pre-allocation
AccCmd = zeros(1, length(T));
VelCmd = zeros(1, length(T));
PosCmd = zeros(1, length(T));
AccMax = 30;
i = 1;
for t = T(1:end-1)
    if(t >= 0 && t < Tk(1))
        AccCmd(i) = AccMax;
    elseif(t >= Tk(1) && t < Tk(2))
        AccCmd(i) = -AccMax;
    elseif(t >= Tk(2) && t < Tk(3))
        AccCmd(i) = AccMax;
    elseif(t >= Tk(3) && t < Tk(4))
        AccCmd(i) = 0;
    end
    VelCmd(i+1) = VelCmd(i) + AccCmd(i)*(sampT);
    PosCmd(i+1) = PosCmd(i) + VelCmd(i)*sampT + sampT*sampT*AccCmd(i)/2;
    i = i+1;
end

%% Output File
fileID = fopen('curve.txt', 'w');
for i=1:length(T)
    fprintf(fileID, '%f\t%f\t%f\n', PosCmd(i), VelCmd(i),  AccCmd(i));
end
fclose(fileID);

%% Plot
figure('Name','Acc & Vel & Pos Commands', ...
       'NumberTitle','off', ...
       'WindowState','maximized')
subplot(3,1,1)
plot(T, AccCmd);
title('Acceleration')
ylabel('rad/s^2')
grid on

subplot(3,1,2)
plot(T, VelCmd);
title('Velocity')
ylabel('rad/s')
grid on

subplot(3,1,3)
plot(T, PosCmd);
title('Position')
ylabel('rad')
grid on