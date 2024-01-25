#include "Serial.h"
#include "OLED.h"

uint8_t flag = 0;
// uint8_t data;
// uint8_t state;
uint8_t Rx_Data[1024];

void SerialInit (void)
{
    // 开启时钟
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);

    // 配置 GPIOA
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOA, &GPIO_InitStruct);

    // 配置 USART
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init (USART1, &USART_InitStruct);
    USART_Cmd (USART1, ENABLE);
    
    // 配置 AFIO
    USART_ITConfig (USART1, USART_IT_RXNE, ENABLE);

    // // 配置 EXTI
    // EXTI_InitTypeDef EXTI_InitStruct;
    // EXTI_InitStruct.EXTI_Line = ;
    // EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    // EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;

    // EXTI_Init (&EXTI_InitStruct);

    // 配置 NVIC
    NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;

    NVIC_Init (&NVIC_InitStruct);
}





void SendByte (uint8_t buffer)
{
    if (USART_GetFlagStatus (USART1, USART_FLAG_TXE) == SET)
    {
        USART_SendData (USART1, buffer);
        while (USART_GetFlagStatus (USART1, USART_FLAG_TXE) == SET);
    }
}

void SendArray (uint8_t* arry, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
    {
        SendByte (arry[i]);
    }
    
}

void SendString (char* string)
{
    for (uint8_t i = 0; string[i] != '\0'; i++)
    {
        SendByte (string[i]);
    }
}

void SendNum (uint32_t num, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
    {
        SendByte (num / (int)pow (10, length - i - 1) % 10 + '0');
    }
    
}

// uint8_t GetData (void)
// {
//     if (state)
//     {
//         state = 0;
//         return data;
//     }
//     return 0;
// }

void USART1_IRQHandler (void)
{
    static uint8_t state = 0;
    static uint8_t pdata = 0;

    if (USART_GetITStatus (USART1, USART_IT_RXNE) == SET)
    {
        uint8_t buffer = USART_ReceiveData (USART1);
        if (state == 0)
        {
            if (buffer == '@' && flag != 1)
            {
                state = 1;
                pdata = 0;
            }
        }
        else if (state == 1)
        {
            if (buffer != '\n')
            {
                Rx_Data[pdata] = buffer;
                pdata++;
            }
            else
            {
                Rx_Data[pdata] = '\0';
                state = 0;
                pdata = 0;
                flag = 1;
            }
            
        }
        // OLED_ShowHexNum (2, 1, data, 2);
        USART_ClearITPendingBit (USART1, USART_IT_RXNE);
    }
    
}

