clc, clear, close all;

sampT=0.001;
position_cmd = zeros(1,10/sampT);    
velocity_cmd = zeros(1,10/sampT);     
acceleration_cmd = zeros(1,10/sampT);  

i=1;
for t=0:sampT:10-sampT
    if(t>=0 && t<2)
       acceleration_cmd(i) = 30;
    elseif(t>=2 && t<6)
        acceleration_cmd(i) = -30;
    elseif(t>=6 && t<8)
        acceleration_cmd(i) = 30;
    elseif(t>=8 && t<=10)
        acceleration_cmd(i) = 0;
    end
    
    velocity_cmd(i+1) = velocity_cmd(i) + acceleration_cmd(i)*sampT;
    position_cmd(i+1) = position_cmd(i) + velocity_cmd(i)*sampT + 0.5*acceleration_cmd(i)*sampT*sampT;

    i = i+1;
    if(i==10/sampT)
        break;
    end
end

%% 畫圖
time = 0:sampT:10-sampT;

figure(1)
subplot(3,1,1)
plot(time,acceleration_cmd);
title('加速度命令規劃','FontSize',12);
legend('加速度命令規劃');
xlabel('time');
ylabel('acceleration');

subplot(3,1,2)
plot(time,velocity_cmd);
title('速度命令規劃','FontSize',12);
legend('速度命令規劃');
xlabel('time');
ylabel('velocity'); 

subplot(3,1,3)
plot(time,position_cmd);
title('位置命令規劃','FontSize',12);
legend('位置命令規劃');
xlabel('time');
ylabel('position'); 

%% 存入txt
fid = fopen('command.txt','wt');
i=1;
for t = 0:sampT:10-sampT
    fprintf(fid,'%f\t',position_cmd(i));
    fprintf(fid,'%f\t',velocity_cmd(i));
    fprintf(fid,'%f\n',acceleration_cmd(i));
    i = i+1;
    if(i==10/sampT)
        break;
    end
end
fclose(fid);
    