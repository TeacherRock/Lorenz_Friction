#ifndef MOTIONCARD
#define MOTIONCARD

#include "IMCDriver.h"
#include "IMCDefine.h"
#include <stdio.h>
#include "Setting.h"

void MotionCard_OpenCard();
void MotionCard_CloseCard();
void MotionCard_ServoOn();
void MotionCard_Serco_Off();
void MotionCard_Encoder(double(&JointEncRad));
void MotionCard_DAC(double(&JointTorCtrl));
void MotionCard_DAC(double(&JointTorCtrl), double(&Voltage));
void MotionCard_ChangeTimer(TMRISR Timer);
void MotionCard_ADC(float(&ADCVoltage)[8]);
#endif