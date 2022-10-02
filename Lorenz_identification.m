clc, clear, close all;

Axis = 1;
%% Jm estimation
disp("========================== Jm estimation ==========================");
Jm_num = 10;
Jm = zeros(1, Jm_num);
for i = 1 : Jm_num
    Data_Jm = load("Data\Lorenz_Jm_" + int2str(i) + ".txt");
    Pos     = Data_Jm(:, 1 + Axis*0 : Axis + Axis*0);
    Vel     = Data_Jm(:, 1 + Axis*1 : Axis + Axis*1);
    PosCmd  = Data_Jm(:, 1 + Axis*2 : Axis + Axis*2);
    VelCmd  = Data_Jm(:, 1 + Axis*3 : Axis + Axis*3);
    TorCtrl = Data_Jm(:, 1 + Axis*4 : Axis + Axis*4);
    
    fup = fit(Vel(1000 : 1900), TorCtrl(1000 : 1900), 'poly1');   % 上面的斜率
    fdown = fit(Vel(3000 : 3900), TorCtrl(3000 : 3900), 'poly1'); % 下面的斜率
    Jm(i) = ((fup.p1 - fdown.p1) * (Vel(500) + Vel(1500)) / 2 + fup.p2 - fdown.p2) / 60;
end
avgJm = mean(Jm);
disp("Jm = "); disp(avgJm);

%% Bm estimation
disp("========================== Bm estimation ==========================");
Bm_num = 10;
Bm = zeros(1, Bm_num);
for i = 1 : Bm_num
    Data_Bm = load("Data\Lorenz_Bm_" + int2str(i) + ".txt");    
    Pos     = Data_Bm(:, 1 + Axis*0 : Axis + Axis*0);
    Vel     = Data_Bm(:, 1 + Axis*1 : Axis + Axis*1);
    PosCmd  = Data_Bm(:, 1 + Axis*2 : Axis + Axis*2);
    VelCmd  = Data_Bm(:, 1 + Axis*3 : Axis + Axis*3);
    TorCtrl = Data_Bm(:, 1 + Axis*4 : Axis + Axis*4);
    
    f = fit(Vel(1000 : 1900), TorCtrl(1000 : 1900), 'poly1');
    Bm(i) = f.p1;
end
avgBm = mean(Bm);
disp("Bm = "); disp(avgBm);

%% Fc estimation
disp("========================== Fc estimation ==========================");
Fc_num = 10;
Fc_p = zeros(1, Fc_num);
Fc_n = zeros(1, Fc_num);
for i = 1 : Fc_num
    Data_Fc = load("Data\Lorenz_Fc_" + int2str(i) + ".txt");
    Pos     = Data_Fc(:, 1 + Axis*0 : Axis + Axis*0);
    Vel     = Data_Fc(:, 1 + Axis*1 : Axis + Axis*1);
    PosCmd  = Data_Fc(:, 1 + Axis*2 : Axis + Axis*2);
    VelCmd  = Data_Fc(:, 1 + Axis*3 : Axis + Axis*3);
    TorCtrl = Data_Fc(:, 1 + Axis*4 : Axis + Axis*4);
    
    fup = fit(Vel(1000 : 1900), TorCtrl(1000 : 1900), 'poly1');   % 速度 > 0
    fdown = fit(Vel(5000 : 5900), TorCtrl(5000 : 5900), 'poly1'); % 速度 < 0

    Fc_p(i) = fup.p2;
    Fc_n(i) = fdown.p2;
end
avgFc_p = mean(Fc_p);
avgFc_n = mean(Fc_n);
disp("when v > 0,"); disp("Fc = "); disp(avgFc_p);
disp("when v < 0,"); disp("Fc = "); disp(avgFc_n);

%% Fs estimation
disp("========================== Fs estimation ==========================");
Fs_num = 10;
Fs_p = zeros(1, Fs_num);
Fs_n = zeros(1, Fs_num);
for i = 1 : Fs_num
    Data_Fs = load("Data\Lorenz_Fs_" + int2str(i) + ".txt");
    Pos     = Data_Fs(:, 1 + Axis*0 : Axis + Axis*0);
    Vel     = Data_Fs(:, 1 + Axis*1 : Axis + Axis*1);
    PosCmd  = Data_Fs(:, 1 + Axis*2 : Axis + Axis*2);
    VelCmd  = Data_Fs(:, 1 + Axis*3 : Axis + Axis*3);
    TorCtrl = Data_Fs(:, 1 + Axis*4 : Axis + Axis*4);

    Fs_p(i) = max(TorCtrl(1 : 1000));
    Fs_n(i) = min(TorCtrl(3500 : 4500));
end
avgFs_p = mean(Fs_p);
avgFs_n = mean(Fs_n);
disp("when v > 0,"); disp("Fs = "); disp(avgFs_p);
disp("when v < 0,"); disp("Fs = "); disp(avgFs_n);





