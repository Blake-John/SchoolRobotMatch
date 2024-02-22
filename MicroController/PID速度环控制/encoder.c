//
// Created by DTS on 2024/2/20.
//

#include "encoder.h"
#include "oled.h"
Motor Motor1;
static uint8_t countone = 0;
static float goalspeed = 3;
uint16_t Compare = 4000;
uint8_t Light = 0;
/**
  * @brief 初始化必要外设
  */
void Motor_Init(void)
{
    HAL_TIM_Encoder_Start(&ENCODER_TIM, TIM_CHANNEL_ALL); //编码器定时器，启动
    __HAL_TIM_ENABLE_IT(&ENCODER_TIM,TIM_IT_UPDATE); //启动编码器定时器更新中断，防溢出
    HAL_TIM_Base_Start_IT(&GAP_TIM); //10Hz间隙定时器，启动
    HAL_TIM_PWM_Start(&DRIVE_TIM,TIM_CHANNEL_1); //PWM输出，启动
    __HAL_TIM_SET_COUNTER(&ENCODER_TIM,10000); //将编码器定时器初始计数值设为10000
    Motor1.LastCount = 0;
    Motor1.TotalCount = 0;
    Motor1.Speed = 0;
    Motor1.OverFlowCount = 0;
    Motor1.Direct = 0;
}

//复写定时器回调函数，用于计算速度
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim -> Instance == ENCODER_TIM.Instance) //编码器输出定时器溢出
    {
        if(COUNTER_NUM < 10000) Motor1.OverFlowCount++; //向上溢出
        else if(COUNTER_NUM >= 10000) Motor1.OverFlowCount--; //向下溢出
        __HAL_TIM_SetCounter(&ENCODER_TIM, 10000); //重置编码器定时器至初始值

    }
    else if(htim -> Instance == GAP_TIM.Instance) //间隔定时器触发中断，计算速度
    {
//        Motor1.Direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM); //通过编码器定时器的计数方向得到电机转动方向，正转返回0，反转返回1
        Motor1.TotalCount = COUNTER_NUM + Motor1.OverFlowCount * AUTO_RELOAD_VALUE; //总计数次数
        Motor1.Speed = (float)(Motor1.TotalCount - Motor1.LastCount) / (4 * MOTOR_SPEED_DOWN_RATIO * PULSE_PER_ROUND) * 10; //计算电机运行速度
        Motor1.LastCount = Motor1.TotalCount; //将本次计数赋给LastCount供下次使用
// 计数器调试代码
//        if (Light == 0)
//        {
//            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
//            Light = 1;
//        }else if (Light == 1)
//        {
//            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
//            Light = 0;
//        }

// 以下屏蔽OLED的慢速魅力时刻
//        if(Motor1.Speed > 0)
//        {
//            OLED_ShowChar(1,10,'F');
//        }else if(Motor1.Speed < 0)
//        {
//            Motor1.Speed = -Motor1.Speed;
//            OLED_ShowChar(1,10,'B');
//        }else
//        {
//            OLED_ShowChar(1,10,'S');
//        }
//        OLED_ShowNum(1,1,(uint32_t)(Motor1.Speed * 1),8);
//        OLED_ShowNum(2,1,++countone,8);
//        OLED_ShowNum(3,1,COUNTER_NUM,8);
        if(Compare > 0 && Compare < 9999)
        {
            if(Motor1.Speed < goalspeed)
            {
                Compare+=100;
                __HAL_TIM_SET_COMPARE(&DRIVE_TIM,TIM_CHANNEL_1,Compare);
            }
            if(Motor1.Speed > goalspeed)
            {
                Compare-=100;
                __HAL_TIM_SET_COMPARE(&DRIVE_TIM,TIM_CHANNEL_1,Compare);
            }
        }
//        OLED_ShowNum(4,1,Compare,8);
    }
}