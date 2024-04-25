//
// Created by DTS on 2024/3/9.
//
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "usart.h"

#ifndef ROBOTMATCHZET6_ENCODE_H
#define ROBOTMATCHZET6_ENCODE_H

//定时器编号
#define ENCODERRACK_TIM htim1
#define ENCODERFL_TIM htim2 //编码器定时器
#define ENCODERFR_TIM htim3
#define ENCODERBL_TIM htim4
#define ENCODERBR_TIM htim5

#define MOTOR_FL_FR_BL_BR_TIM htim1 //PWM输出定时器
#define GAP_TIM htim6 //计算间隙定时器

#define MOTOR_SPEED_DOWN_RATIO 20u //电机减速比x:1
#define PULSE_PER_ROUND 13 //单圈脉冲
#define TYRE_RADIUS 34 //轮胎半径(mm)
#define LINE_SPEED (TYRE_RADIUS * 3.14 * 2) //线速度

#define AUTO_RELOAD_VALUE_FL __HAL_TIM_GetAutoreload(&ENCODERFL_TIM) //编码器定时器的自动装载值
#define AUTO_RELOAD_VALUE_FR __HAL_TIM_GetAutoreload(&ENCODERFR_TIM)
#define AUTO_RELOAD_VALUE_BL __HAL_TIM_GetAutoreload(&ENCODERBL_TIM)
#define AUTO_RELOAD_VALUE_BR __HAL_TIM_GetAutoreload(&ENCODERBR_TIM)
#define COUNTER_NUM_FL __HAL_TIM_GetCounter(&ENCODERFL_TIM) //编码定时器的计数
#define COUNTER_NUM_FR __HAL_TIM_GetCounter(&ENCODERFR_TIM)
#define COUNTER_NUM_BL __HAL_TIM_GetCounter(&ENCODERBL_TIM)
#define COUNTER_NUM_BR __HAL_TIM_GetCounter(&ENCODERBR_TIM)
#define COUNTER_NUM_SHOVEL __HAL_TIM_GetCounter(&ENCODERRACK_TIM)

//获取电机参数的结构体
typedef struct Motor
{
    uint16_t PWM_OUT;
    double Speed; //电机转速
    double Error;
    double Last_Error;
    double Integral;
    double TargetSpeed;
}Motor;

typedef struct Motor_Rack
{
    int32_t Targetposition;
    int32_t Position;
    int32_t Posi_Error;
    uint16_t PWM_OUT;
    double P;
    double Speed; //电机转速
    double Error;
    double Last_Error;
    double Integral;
    double TargetSpeed;
}Motor_Rack;

void MotorEncode_Init(void);
void Set_Target_Speed(float Speed);
void PID_Calculate(Motor* Motor_Side);

#endif //ROBOTMATCHZET6_ENCODE_H
