/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA1
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "delay.h"
#include "KEY.h"
#include "timer.h"
#include "OLED.h"
#include "Serial.h"

uint16_t duty1 = 1000, duty2 = 1450;
uint32_t px = 0, py = 0;
uint32_t dx = 0, dy = 0;
int key = 0;

void showx (void)
{
    OLED_ShowString (3, 1, "x : ");
    OLED_ShowNum (3, 5, dx, 3);
    OLED_ShowChar (3, 8, '.');
    OLED_ShowNum (3, 9, px, 1);
}

void showy (void)
{
    OLED_ShowString (4, 1, "y : ");
    OLED_ShowNum (4, 5, dy, 3);
    OLED_ShowChar (4, 8, '.');
    OLED_ShowNum (4, 9, py, 1);
}

int main()
{
    Timer_Init ();
    // Key_Init ();
    // Key_InitA ();
    OLED_Init ();
    SerialInit ();
    // OLED_ShowString (1, 3, "Hello STM32 !");
    OLED_ShowChar (1, 1, 'X');
    OLED_ShowChar (3, 1, 'Y');
    // showx ();
    // showy ();
    TIM_SetCompare2 (TIM2, 1000);
    TIM_SetCompare3 (TIM2, 1450);

    float dx, dy;
    uint8_t count = 0;

    while (1)
    {
        if (flag == 2)
        {
            TIM_SetCompare2 (TIM2, 1000);
            TIM_SetCompare3 (TIM2, 1450);
            flag = 0;
            OLED_ShowString (2, 1, "                ");
            OLED_ShowString (4, 1, "                ");
        }
        
        if (flag == 1)
        {
            OLED_ShowString (2, 1, "                ");
            OLED_ShowString (4, 1, "                ");
            // X12.3Y3.2
            // char bufx[10];
            char* p;
            uint8_t i = 1, j = 0;
            for (; Rx_Data[i] != 'Y' && Rx_Data[i] != 'y'; i++)
            {
                // bufx[i - 1] = Rx_Data[i];
                OLED_ShowChar (2, i, Rx_Data[i]);
            }
            j = i + 1;
            dx = strtof (Rx_Data + 1, &p);
            // char bufy[10];
            for (; Rx_Data[j] != '\0' && Rx_Data[j] != ' ';j++)
            {
                // bufy[j - i - 1] = Rx_Data[j];
                OLED_ShowChar (4, j - i, Rx_Data[j]);
            }
            dy = strtof (p + 1, NULL);
            int32_t duty_dx, duty_dy;
            duty_dx = (int)(dx / 0.09f);
            duty_dy = (int)(dy / 0.09f);
            duty1 += -(int)duty_dx;
            duty2 += -(int)duty_dy;
            
            // if (duty1 >= 2500)
            // {
            //     duty1 = 2500;
            // }
            if (duty1 <= 0)
            {
                duty1 = 0;
            }
            // if (duty2 >= 2500)
            // {
            //     duty2 = 2500;
            // }
            // if (duty2 <= 1450)
            // {
            //     duty2 = 1450;
            // }
            
            TIM_SetCompare2 (TIM2, duty1);
            OLED_ShowNum (1, 3, count++, 2);
            // for (; Rx_Data[i] != 'Y' && Rx_Data[i] != 'y'; i++)
            // {
            //     // bufx[i - 1] = Rx_Data[i];
            //     OLED_ShowChar (2, i, Rx_Data[i]);
            // }
            TIM_SetCompare3 (TIM2, duty2);
            OLED_ShowNum (3, 3, count++, 2);
            // for (; Rx_Data[j] != '\0' && Rx_Data[j] != ' ';j++)
            // {
            //     // bufy[j - i - 1] = Rx_Data[j];
            //     OLED_ShowChar (4, j - i, Rx_Data[j]);
            // }

            flag = 0;
        }

    }
    



    // while (1)
    // {
    //     if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_0) == 0)
    //     {
    //         Delay_ms (20);
    //         while (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_0) == 0)
    //         {
    //             duty1 += 5;
    //             dx += 4;
    //             px += 5;
    //             if (px == 10)
    //             {
    //                 px = 0;
    //                 dx++;
    //             }
    //             if (duty1 > 250)
    //             {
    //                 duty1 = 250;
    //             }
    //             if (dx >= 180)
    //             {
    //                 dx = 180;
    //                 px = 0;
    //             }
    //             TIM_SetCompare2 (TIM2, duty1);
    //             showx ();
    //             Delay_ms (100);
    //         }
    //         Delay_ms (20);
    //     }
        
    //     if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_10) == 0)
    //     {
    //         Delay_ms (20);
    //         while (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_10) == 0)
    //         {
    //             duty2 += 5;
    //             dy += 4;
    //             py += 5;
    //             if (py == 10)
    //             {
    //                 py = 0;
    //                 dy++;
    //             }
    //             if (duty2 > 250)
    //             {
    //                 duty2 = 250;
    //             }
    //             if (dy >= 108)
    //             {
    //                 dy = 108;
    //                 py = 0;
    //             }
    //             TIM_SetCompare3 (TIM2, duty2);
    //             showy ();
    //             Delay_ms (100);
    //         }
    //         Delay_ms (20);
    //     }

    //     if (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_11) == 1)
    //     {
    //         Delay_ms (20);
    //         while (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_11) == 1)
    //         {
    //             duty1 -= 5;
    //             if (dx <= 5)
    //             {
    //                 dx = 0;
    //                 px = 0;
    //             }
    //             else
    //             {
    //                 dx -= 5;
    //                 px += 5;
    //             }
    //             if (px == 10)
    //             {
    //                 px = 0;
    //                 dx++;
    //             }
    //             if (duty1 < 50)
    //             {
    //                 duty1 = 50;
    //             }
    //             TIM_SetCompare2 (TIM2, duty1);
    //             showx ();
    //             Delay_ms (100);
    //         }
    //         Delay_ms (20);
    //     }

    //     if (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9) == 1)
    //     {
    //         Delay_ms (20);
    //         while (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9) == 1)
    //         {
    //             duty2 -= 5;
    //             if (dy <= 5)
    //             {
    //                 dy = 0;
    //                 py = 0;
    //             }
    //             else
    //             {
    //                 dy -= 5;
    //                 py += 5;
    //             }
    //             if (py == 10)
    //             {
    //                 py = 0;
    //                 dy++;
    //             }
    //             if (duty2 < 130)
    //             {
    //                 duty2 = 130;
    //             }
    //             TIM_SetCompare3 (TIM2, duty2);
    //             showy ();
    //             Delay_ms (100);
    //         }
    //         Delay_ms (20);
    //     }
    // }
    

}
