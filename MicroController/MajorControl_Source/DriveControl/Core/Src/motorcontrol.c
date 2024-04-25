//
// Created by DTS on 2024/3/11.
//

#include "motorcontrol.h"


void Motor_Init(void)
{
    HAL_TIM_PWM_Init(&htim1);
    HAL_TIM_PWM_Init(&htim2);
    HAL_TIM_PWM_Init(&htim3);
    HAL_TIM_PWM_Init(&htim4);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//T_FL
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//T_FR
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);//T_BL
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);//T_BR
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//T_Rack
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//T_Roller
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//T_Trans
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//T_S_CamOne
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//T_S_CamTwo
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//T_S_Roller_Rise
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);//T_S_Trans_Fold
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//Sustainer_Right
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//Sustainer_Left
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//T_S_Shovel
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);//Spare
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);//Spare
}


void Motor_PWM_Out(uint16_t Motor_Side, uint16_t Motor_Speed)
{
    switch (Motor_Side)
    {
        case 1://FL
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Motor_Speed);
            break;
        }
        case 2://FR
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Motor_Speed);
            break;
        }
        case 3://BL
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Motor_Speed);
            break;
        }
        case 4://BR
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motor_Speed);
            break;
        }
        case 5://BR
        {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Motor_Speed);
            break;
        }
        case 6://Rack
        {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, Motor_Speed);
            break;
        }
        case 7://Roller
        {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, Motor_Speed);
            break;
        }
        case 8://Trans
        {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, Motor_Speed);
            break;
        }

            // The next part is about servos
        case 9://S_CamOne
        {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, Motor_Speed);
            break;
        }
        case 10://S_CamTwo
        {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, Motor_Speed);
            break;
        }
        case 11://S_Roller_Rise
        {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Motor_Speed);
            break;
        }
        case 12://S_Trans_Fold
        {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, Motor_Speed);
            break;
        }
            //The next part is not defined yet
        case 13://NaN
        {
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Motor_Speed);
            break;
        }
        case 14://NaN
        {
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, Motor_Speed);
            break;
        }
        case 15://NaN
        {
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, Motor_Speed);
            break;
        }
        case 16://NaN
        {
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, Motor_Speed);
            break;
        }

        default:
        {
        }
    }

}