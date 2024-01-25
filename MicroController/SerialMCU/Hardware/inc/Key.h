#pragma once

#include "stm32f10x.h"
#include "delay.h"

void KeyInit (uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin);
uint8_t GetKey (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);
