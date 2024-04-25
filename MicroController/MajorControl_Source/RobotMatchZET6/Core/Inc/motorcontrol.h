//
// Created by DTS on 2024/3/10.
//
#include "encode.h"

#ifndef ROBOTMATCHZET6_MOTORCONTROL_H
#define ROBOTMATCHZET6_MOTORCONTROL_H

void Motor_Init(void);
void Motor_Set_Speed_Single(Motor Motor_Side, uint16_t Speed);
void Car_Seize(void);
void Car_Forward(void);
void Car_Backward(void);
void Car_Counter_Clockwise(void);
void Car_Clockwise(void);
void Car_Leftward(void);
void Car_Rightward(void);
void Rack_Forward();
void Rack_Backward();
void Rack_Seize();
void Roller_Forward();
void Roller_Seize();
void Trans_Seize();
void Trans_Run();


#endif //ROBOTMATCHZET6_MOTORCONTROL_H
