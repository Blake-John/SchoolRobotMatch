//
// Created by DTS on 2024/3/10.
//

#include "motorcontrol.h"
#include "encode.h"
#include "usart.h"


void Car_Backward()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_SET);

}

void Car_Forward()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_RESET);
}

void Car_Rightward()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_RESET);
}

void Car_Leftward()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_SET);
}

void Car_Counter_Clockwise()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_RESET);
}

void Car_Clockwise()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_SET);
}

void Car_Seize()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_SET);
}

void Roller_Forward()
{
    HAL_GPIO_WritePin(Roller_Motivate_GPIO_Port,Roller_Motivate_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Roller_Slave_GPIO_Port,Roller_Slave_Pin,GPIO_PIN_SET);
}

void Roller_Seize()
{
    HAL_GPIO_WritePin(Roller_Motivate_GPIO_Port,Roller_Motivate_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(Roller_Slave_GPIO_Port,Roller_Slave_Pin,GPIO_PIN_SET);
}

void Rack_Forward()
{
    HAL_GPIO_WritePin(Rack_Motivate_GPIO_Port, Rack_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Rack_Slave_GPIO_Port, Rack_Slave_Pin, GPIO_PIN_SET);
}

void Trans_Seize()
{
    HAL_GPIO_WritePin(Trans_Motivate_GPIO_Port,Trans_Motivate_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(Trans_Slave_GPIO_Port,Trans_Slave_Pin,GPIO_PIN_SET);
}

void Trans_Run()
{
    HAL_GPIO_WritePin(Trans_Motivate_GPIO_Port,Trans_Motivate_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(Trans_Slave_GPIO_Port,Trans_Slave_Pin,GPIO_PIN_RESET);
}

void Rack_Backward()
{
    HAL_GPIO_WritePin(Rack_Motivate_GPIO_Port, Rack_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Rack_Slave_GPIO_Port, Rack_Slave_Pin, GPIO_PIN_RESET);
}

void Rack_Seize()
{
    HAL_GPIO_WritePin(Rack_Motivate_GPIO_Port, Rack_Motivate_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Rack_Slave_GPIO_Port, Rack_Slave_Pin, GPIO_PIN_SET);
}

void Motor_Init()
{
    HAL_GPIO_WritePin(MotorFL_Motivate_GPIO_Port, MotorFL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFL_Slave_GPIO_Port, MotorFL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Motivate_GPIO_Port, MotorFR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorFR_Slave_GPIO_Port, MotorFR_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Motivate_GPIO_Port, MotorBL_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBL_Slave_GPIO_Port, MotorBL_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Motivate_GPIO_Port, MotorBR_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MotorBR_Slave_GPIO_Port, MotorBR_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Roller_Motivate_GPIO_Port, Roller_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Roller_Slave_GPIO_Port, Roller_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Rack_Motivate_GPIO_Port, Rack_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Rack_Slave_GPIO_Port, Rack_Slave_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Trans_Motivate_GPIO_Port, Trans_Motivate_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Trans_Slave_GPIO_Port, Trans_Slave_Pin, GPIO_PIN_RESET);
}