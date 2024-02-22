//
// Created by DTS on 2024/2/20.
//

#ifndef PIDCONTROL_ENCODER_H
#define PIDCONTROL_ENCODER_H
#include "stm32f1xx_hal.h"
#include "tim.h"

//电机编码器输入引脚(AB相)
#define MOTOR1_ENCODER1_PORT GPIOA
#define MOTOR1_ENCODER1_PIN GPIO_PIN_0
#define MOTOR1_ENCODER2_PORT GPIOA
#define MOTOR1_ENCODER2_PIN GPIO_PIN_1

//定时器编号
#define ENCODER_TIM htim2 //编码器定时器
#define DRIVE_TIM htim3 //PWM输出定时器
#define GAP_TIM htim4 //计算间隙定时器

#define MOTOR_SPEED_DOWN_RATIO 48u //电机减速比x:1
#define PULSE_PER_ROUND 13 //单圈脉冲
#define TYRE_RADIUS 33 //轮胎半径
#define LINE_SPEED (TYRE_RADIUS * 3.14 * 2) //线速度

#define AUTO_RELOAD_VALUE __HAL_TIM_GetAutoreload(&ENCODER_TIM) //编码器定时器的自动装载值
#define COUNTER_NUM __HAL_TIM_GetCounter(&ENCODER_TIM) //编码定时器的计数

//获取电机参数的结构体
typedef struct Motor
{
    int32_t LastCount; //上次计数值
    int32_t TotalCount; //总计数值
    int16_t OverFlowCount; //溢出次数
    float Speed; //电机转速
    uint8_t Direct; //旋转方向
}Motor;

void Motor_Init(void);
#endif //PIDCONTROL_ENCODER_H
