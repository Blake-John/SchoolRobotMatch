//
// Created by DTS on 2024/3/10.
//

#include "servocontrol.h"
extern unsigned char Slave_Send_State;

void Shovel_Down()
{
    Slave_Send_State = 0x24;
}

void Shovel_Up()
{
    Slave_Send_State = 0x25;
}

void Roller_Up()
{
    Slave_Send_State = 0x41;
}

void Roller_Down()
{
    Slave_Send_State = 0x40;
}

void Sustainer_Up()
{
    Slave_Send_State = 0x45;
}

void Sustainer_Down()
{
    Slave_Send_State = 0x44;
}
