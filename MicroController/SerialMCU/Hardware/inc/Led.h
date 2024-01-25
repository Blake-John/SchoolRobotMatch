#pragma once

#include "stm32f10x.h"

typedef enum
{
    ON = 0,
    OFF
}LedAction;

void LedInit (uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed);
void LedTurn (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, LedAction state);
