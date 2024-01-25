#pragma once

#include "stm32f10x.h"
#include "math.h"

extern uint8_t flag;
extern uint8_t Rx_Data[];

void SerialInit (void);
void SendByte (uint8_t buffer);
// uint8_t GetData (void);
void SendArray (uint8_t* arry, uint8_t length);
void SendString (char* string);
void SendNum (uint32_t num, uint8_t length);

