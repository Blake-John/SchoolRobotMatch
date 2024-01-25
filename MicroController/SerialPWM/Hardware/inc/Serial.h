#pragma once

#include "stm32f10x.h"
#include <stdlib.h>

extern uint8_t Rx_Data[];
extern uint8_t flag;

void SerialInit (void);
