//
// Created by DTS on 2024/3/8.
//

#include "oled.h"

extern char SaveDataOne[4][17];
extern char SaveDataTwoA[4][17];
extern char SaveDataTwoB[4][17];
extern char SaveDataTwoC[4][17];
extern char SaveDataTwoD[4][17];
extern char Data_Category[4][17];
extern unsigned char txbuf[32];
extern unsigned char Menu_Level;
extern unsigned char Focus_Line;
extern unsigned char Up_Limit;
extern unsigned char Down_Limit;
extern unsigned char SaveData_Should_Cpy;


void Control_Down()
{
    Cpy_Check();
    if (Focus_Line < Down_Limit) //The focus is on 1,2 or 3 Line
    {
        {
            OLED_ShowString(Focus_Line, 1, Data_Category[Focus_Line - 1]);
            OLED_BlackWhite_Switch(++Focus_Line);
        }
    } else
    {
        OLED_ShowString(Down_Limit, 1, Data_Category[Down_Limit - 1]);
        OLED_BlackWhite_Switch(Up_Limit);
        Focus_Line = Up_Limit;
    }
}

void Control_Up()
{
    Cpy_Check();
    if (Focus_Line > Up_Limit)
    {
        OLED_ShowString(Focus_Line, 1, Data_Category[Focus_Line - 1]);
        OLED_BlackWhite_Switch(--Focus_Line);
    } else
    {
        OLED_ShowString(Up_Limit, 1, Data_Category[Up_Limit - 1]);
        OLED_BlackWhite_Switch(Down_Limit);
        Focus_Line = Down_Limit;
    }
}

void Control_Into()
{

}

void Control_Exit()
{

}

void Control_Init()
{
    SaveData_Should_Cpy = 1;
    OLED_BlackWhite_Switch(1);
    Focus_Line = 1;
}

void Menu_Sec_Init()
{
    SaveData_Should_Cpy = 1;
    OLED_BlackWhite_Switch(Up_Limit);
    Focus_Line = Up_Limit;
}

void Menu_Roller_Start_Stop()
{
    txbuf[4] |= 0x01;
}


void Menu_Roller_Up()
{
    txbuf[4] |= 0x02;
}

void Menu_Roller_Down_Regi()
{
    txbuf[4] |= 0x04;
}

void Menu_Trans_Start_Stop()
{
    txbuf[4] |= 0x08;
}

void Menu_Trans_Fold()
{
    txbuf[4] |= 0x10;
}

void Menu_Trans_Defold()
{
    txbuf[4] |= 0x20;
}

void Menu_Shovel_Auto_Once()
{
    txbuf[4] |= 0x40;
}

void Menu_Shovel_MenualMode()
{
    txbuf[4] |= 0x80;
}

void Menu_Camera_Laser()
{
    txbuf[5] |= 0x01;
}

void Menu_Camera_DetectMode()
{
    txbuf[5] |= 0x02;
}