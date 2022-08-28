MeasuredData = load('Lorenz_Fc_10.txt');
nAxis = 1;
Axis = 1;

Pos     = MeasuredData(:, 1 + Axis*0 : Axis + Axis*0);
Vel     = MeasuredData(:, 1 + Axis*1 : Axis + Axis*1);
PosCmd  = MeasuredData(:, 1 + Axis*2 : Axis + Axis*2);
VelCmd  = MeasuredData(:, 1 + Axis*3 : Axis + Axis*3);
TorCtrl = MeasuredData(:, 1 + Axis*4 : Axis + Axis*4);

fup=fit(Vel(1000:1900),TorCtrl(1000:1900),'poly1');
fdown=fit(Vel(5000:5900),TorCtrl(5000:5900),'poly1');