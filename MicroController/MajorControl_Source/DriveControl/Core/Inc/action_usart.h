//
// Created by DTS on 2024/3/23.
//
#include "stm32f1xx_hal.h"
#include "tim.h"
#ifndef DRIVECONTROL_ACTION_USART_H
#define DRIVECONTROL_ACTION_USART_H

// The region of servo COMPARE is from 50 t0 250
#define ROLLER_UP_COMPARE       0x4D

#define ROLLER_DOWN_COMPARE     0xE9
#define ROLLER_INITIAL_COMPARE  0xC6
#define SHOVEL_INITIAL_COMPARE  0x32
#define SUSTAINER_LEFT_UP_COMPARE    0xE2
#define SUSTAINER_LEFT_DOWN_COMPARE  0x32
#define SUSTAINER_RIGHT_UP_COMPARE    0x42
#define SUSTAINER_RIGHT_DOWN_COMPARE  0xFA
#define Trans_FOLD_COMPARE      0xDC
#define Trans_UNFOLD_COMPARE    0x70

// The Motor initial COMPARE
#define RACK_MOTOR_COMPARE              600
#define TRANS_MOTOR_COMPARE             700
#define ROLLER_MOTOR_COMPARE_SLOW       820

void Menu_Action(uint8_t Menu_State);
void PID_Motor_Action(uint8_t PWMOUT[10]);


#endif //DRIVECONTROL_ACTION_USART_H
