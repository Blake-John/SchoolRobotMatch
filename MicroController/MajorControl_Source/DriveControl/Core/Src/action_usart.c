//
// Created by DTS on 2024/3/23.
//

#include "action_usart.h"

uint8_t Shovel_Manual_State = 0;
extern unsigned char Detect_State;
unsigned char Sustain_State = 0;
unsigned char Roller_State = 0;
unsigned char Shovel_Compare = 50;
unsigned char Boost_State = 0;
unsigned char Shovel_WaitCount = 0;

void Trans_Fold_Unfold(uint8_t state)
{
    if ((state & 0x01) == 0x01)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Trans_UNFOLD_COMPARE);
    } else if ((state & 0x01) == 0x00)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Trans_FOLD_COMPARE);
    }
}


void Camera_Detect(uint8_t state)
{
    if ((state & 0x01) == 0x01)
    {
        Detect_State = 0;
    } else if ((state & 0x01) == 0x01)
    {
        Detect_State = 1;
    }
}

void Menu_Action(uint8_t Menu_State)
{
    switch (Menu_State & 0xFC)
    {
        case 0x10:
            Trans_Fold_Unfold(Menu_State);
            break;
        case 0x20:
            Camera_Detect(Menu_State);
            break;
        default:
        {
        }
    }
    if (Menu_State == 0x41 && Roller_State != 1)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ROLLER_UP_COMPARE);
        HAL_Delay(100);
        Roller_State = 1;
    } else if (Menu_State == 0x40 && Roller_State != 0)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ROLLER_DOWN_COMPARE);
        HAL_Delay(100);
        Roller_State = 0;
    } else if (Menu_State == 0x45 && Sustain_State != 0)
    {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, SUSTAINER_LEFT_UP_COMPARE);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, SUSTAINER_RIGHT_UP_COMPARE);
        HAL_Delay(100);
        Sustain_State = 0;
    } else if (Menu_State == 0x44 && Sustain_State != 1)
    {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, SUSTAINER_LEFT_DOWN_COMPARE);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, SUSTAINER_RIGHT_DOWN_COMPARE);
        HAL_Delay(100);
        Sustain_State = 1;
    } else if (Menu_State == 0x2C)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ROLLER_INITIAL_COMPARE);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, SUSTAINER_LEFT_UP_COMPARE);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, SUSTAINER_RIGHT_UP_COMPARE);
    } else if (Menu_State == 0x25)
    {
        if (Shovel_WaitCount >= 9)
        {
            if (Shovel_Compare <= 50)
            {
                Shovel_Compare = 50;
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Shovel_Compare);
            } else
            {
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Shovel_Compare--);
            }
            Shovel_WaitCount = 0;
        } else
        {
            Shovel_WaitCount++;
        }
    } else if (Menu_State == 0x24)
    {
        if (Shovel_WaitCount >= 9)
        {
            if (Shovel_Compare >= 250)
            {
                Shovel_Compare = 250;
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Shovel_Compare);
            } else
            {
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Shovel_Compare++);
            }
            Shovel_WaitCount = 0;
        } else
        {
            Shovel_WaitCount++;
        }
    } else if (Menu_State == 0x31)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ROLLER_UP_COMPARE);
    } else if (Menu_State == 0x30)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ROLLER_INITIAL_COMPARE);
    } else if (Menu_State == 0x39)
    {
        Boost_State = 1;
    } else if (Menu_State == 0x38)
    {
        Boost_State = 0;
    } else if (Menu_State == 0x21)
    {
        Detect_State = 1;

    }
}

//uint16_t u8_To_u16(uint8_t NumOne, uint8_t NumTwo)  //低位型(Num2在前，Num1在后)
//{
//    uint16_t result = 0;
//    result |= (NumTwo << 8);
//    result |= NumOne;
//    return result;
//
//}

void PID_Motor_Action(uint8_t PWMOUT[10])
{
    uint16_t pwm1 = 0, pwm2 = 0, pwm3 = 0, pwm4 = 0;
    pwm1 |= (PWMOUT[0] << 8);
    pwm1 |= PWMOUT[1];
    pwm2 |= (PWMOUT[2] << 8);
    pwm2 |= PWMOUT[3];
    pwm3 |= (PWMOUT[4] << 8);
    pwm3 |= PWMOUT[5];
    pwm4 |= (PWMOUT[6] << 8);
    pwm4 |= PWMOUT[7];
    if (Boost_State == 1)
    {
        pwm1 = 65000;
        pwm2 = 65300;
        pwm3 = 65000;
        pwm4 = 65000;
    }

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm2);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm3);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pwm4);

}
