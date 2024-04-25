//
// Created by DTS on 2024/3/15.
//

#ifndef ROBOTMATCHZET6_TOVOFA_H
#define ROBOTMATCHZET6_TOVOFA_H
#include "usart.h"

#define UART_PORT &huart2
void Send_To_VOFA(float send);
void Send_To_VOFA_Double(double send);
void Send_Head_For_FloatOnly(void);
#endif //ROBOTMATCHZET6_TOVOFA_H
