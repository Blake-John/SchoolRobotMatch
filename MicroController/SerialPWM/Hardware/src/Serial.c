#include "Serial.h"

uint8_t flag = 0;
uint8_t Rx_Data[1024];


void SerialInit (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOA, &GPIO_InitStruct);

    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init (USART1, &USART_InitStruct);
    USART_Cmd (USART1, ENABLE);

    USART_ITConfig (USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init (&NVIC_InitStruct);

}

void USART1_IRQHandler (void)
{
    static uint8_t state = 0;
    static uint8_t p = 0;

    if (USART_GetITStatus (USART1, USART_IT_RXNE) == SET)
    {
        uint8_t buffer = USART_ReceiveData (USART1);
        if (state == 0)
        {
            if (buffer == '@' && flag != 1)
            {
                state = 1;
                p = 0;
            }
        }
        else if (state == 1)
        {
            if (buffer != '\n')
            {
                Rx_Data[p] = buffer;
                p++;
            }
            else
            {
                Rx_Data[p] = '\0';
                state = 0;
                p = 0;
                flag = 1;
            }
        }
        USART_ClearITPendingBit (USART1, USART_IT_RXNE);
    }
}