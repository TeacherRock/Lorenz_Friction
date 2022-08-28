MeasuredData = load('Lorenz_Bm_10.txt');
nAxis = 1;
Axis = 1;

Pos     = MeasuredData(:, 1 + Axis*0 : Axis + Axis*0);
Vel     = MeasuredData(:, 1 + Axis*1 : Axis + Axis*1);
PosCmd  = MeasuredData(:, 1 + Axis*2 : Axis + Axis*2);
VelCmd  = MeasuredData(:, 1 + Axis*3 : Axis + Axis*3);
TorCtrl = MeasuredData(:, 1 + Axis*4 : Axis + Axis*4);

f=fit(Vel(1000:1900),TorCtrl(1000:1900),'poly1');