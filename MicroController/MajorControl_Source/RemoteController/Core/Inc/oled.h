//
// Created by DTS on 2023/12/2.
//
#include "stm32f1xx_hal.h"
#include "string.h"
#include "i2c.h"
#include "string.h"

#ifndef ROBOT2024_OLED_H
#define ROBOT2024_OLED_H
void OLED_Init(void);
void OLED_Clear(void);
void Cpy_Check(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_BlackWhite_Switch(uint8_t Line);
#endif //ROBOT2024_OLED_H
