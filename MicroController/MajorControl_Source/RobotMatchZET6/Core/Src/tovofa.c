//
// Created by DTS on 2024/3/15.
//

#include "tovofa.h"
unsigned char tail[4] = {0x00, 0x00, 0x80, 0x7f};

void Send_Head_For_FloatOnly(void)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        HAL_UART_Transmit(UART_PORT,(uint8_t *)&tail[i],1,0xff);
        while(HAL_UART_GetState(UART_PORT) == RESET);
    }
}

void Send_To_VOFA(float send)
{
    HAL_UART_Transmit(UART_PORT, (uint8_t *)&send, sizeof(float), 0xff);
    while(HAL_UART_GetState(UART_PORT)==RESET);
}
void Send_To_VOFA_Double(double send)
{
    HAL_UART_Transmit(UART_PORT, (uint8_t *)&send, sizeof(double), 0xff);
    while(HAL_UART_GetState(UART_PORT)==RESET);
}