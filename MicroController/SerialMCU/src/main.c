/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA0, PA2
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "Serial.h"
#include "OLED.h"
#include "Led.h"
#include "delay.h"
#include "Key.h"


int main()
{
    SerialInit ();
    OLED_Init ();
    KeyInit (RCC_APB2Periph_GPIOB, GPIOB, GPIO_Mode_IPU, GPIO_Pin_0);
    LedInit (RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_2, GPIO_Speed_50MHz);

    OLED_ShowString (1, 1, "Receive : ");
    OLED_ShowString (3, 1, "Send : ");

    // uint8_t buffer = 0;

    while (1)
    {
        // if (USART_GetFlagStatus (USART1, USART_FLAG_RXNE) == SET)
        // {
        //     buffer = USART_ReceiveData (USART1);
        //     while (USART_GetFlagStatus (USART1, USART_FLAG_RXNE == SET));
        //     LedTurn (GPIOA, GPIO_Pin_2, ON);
        //     Delay_ms (500);
        //     LedTurn (GPIOA, GPIO_Pin_2, OFF);
            
        //     OLED_ShowHexNum (2, 1, buffer, 8);
        //     SendByte (1);
        //     USART_ClearFlag (USART1, USART_FLAG_RXNE);
        // }
        // buffer = GetData ();
        // OLED_ShowHexNum (2, 1, buffer, 8);

        if (GetKey (GPIOB, GPIO_Pin_0, GPIO_Mode_IPU) == 1)
        {
            SendString ("Hello");
            OLED_ShowString (4, 1, "Hello");
        }
        // if (USART_GetITStatus (USART1, USART_IT_RXNE) == SET)
        // {
            
        // }
        if (flag == 1)
        {
            OLED_ShowString (2, 1, "                ");
            for (uint8_t i = 0; Rx_Data[i] != '\0' && Rx_Data[i] != ' '; i++)
            {
                // OLED_ShowHexNum (2, 1 + i, Rx_Data[i], 2);
                OLED_ShowChar (2, 1 + i, Rx_Data[i]);
            }
            flag = 0;
        }
        
    }
    
}
