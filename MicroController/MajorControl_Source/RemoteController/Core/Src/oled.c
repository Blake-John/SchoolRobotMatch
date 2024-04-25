//
// Created by DTS on 2023/12/2.
//

#include "oled.h"
#include "Font.h"
#include "main.h"


#define SSD_Hardware_Slave_Address 0x78
#define SSD_Command_Address 0x00
#define SSD_Data_Address 0x40

extern unsigned char SaveData_Should_Cpy;
extern unsigned char Menu_Level;
char SaveDataOne[4][17] = {0};
char SaveDataTwoA[4][17] = {0};
char SaveDataTwoB[4][17] = {0};
char SaveDataTwoC[4][17] = {0};
char SaveDataTwoD[4][17] = {0};
char Data_Category[4][17] = {0};
extern unsigned char Focus_Line;

void Cpy_Check()
{
    if (SaveData_Should_Cpy == 1)
    {
        switch (Menu_Level)
        {
            case 1:
                memcpy(Data_Category, SaveDataOne, sizeof(SaveDataOne));
                SaveData_Should_Cpy = 0;
                break;
            case 2:
                memcpy(Data_Category, SaveDataTwoA, sizeof(SaveDataTwoA));
                SaveData_Should_Cpy = 0;
                break;
            case 3:
                memcpy(Data_Category, SaveDataTwoB, sizeof(SaveDataTwoA));
                SaveData_Should_Cpy = 0;
                break;
            case 4:
                memcpy(Data_Category, SaveDataTwoC, sizeof(SaveDataTwoA));
                SaveData_Should_Cpy = 0;
                break;
            case 5:
                memcpy(Data_Category, SaveDataTwoD, sizeof(SaveDataTwoA));
                SaveData_Should_Cpy = 0;
                break;
            default:
            {
            }
        }


    }
}

void Oled_Init()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
}


void WriteCmd(uint8_t I2C_Command)
{
    HAL_I2C_Mem_Write(&hi2c1, SSD_Hardware_Slave_Address, SSD_Command_Address, I2C_MEMADD_SIZE_8BIT, &I2C_Command, 1,
                      100);
}

void WriteByte(uint8_t I2C_Data)
{
    HAL_I2C_Mem_Write(&hi2c1, SSD_Hardware_Slave_Address, SSD_Data_Address, I2C_MEMADD_SIZE_8BIT, &I2C_Data, 1, 100);
}

void OLED_SaveData(uint8_t Line, const char *String)
{
    unsigned int i;
    if (Menu_Level == 1)
    {
        for (i = 0; i < strlen(String); i++)
        {
            SaveDataOne[Line - 1][i] = String[i];
        }
        SaveDataOne[Line - 1][i] = 0xff;
    }
    if (Menu_Level == 1)
    {
        for (i = 0; i < strlen(String); i++)
        {
            SaveDataOne[Line - 1][i] = String[i];

        }
        SaveDataOne[Line - 1][i] = 0xff;
    }

    for (i = 0; i < strlen(String); i++)
    {
        switch (Menu_Level)
        {
            case 1:
                SaveDataOne[Line - 1][i] = String[i];
                break;
            case 2:
                SaveDataTwoA[Line - 1][i] = String[i];
                break;
            case 3:
                SaveDataTwoB[Line - 1][i] = String[i];
                break;
            case 4:
                SaveDataTwoC[Line - 1][i] = String[i];
                break;
            case 5:
                SaveDataTwoD[Line - 1][i] = String[i];
                break;
            default:
            {
            }
        }
    }
    switch (Menu_Level)
    {
        case 1:
            SaveDataOne[Line - 1][i] = 0xff;
            break;
        case 2:
            SaveDataTwoA[Line - 1][i] = 0xff;
            break;
        case 3:
            SaveDataTwoB[Line - 1][i] = 0xff;
            break;
        case 4:
            SaveDataTwoC[Line - 1][i] = 0xff;
            break;
        case 5:
            SaveDataTwoD[Line - 1][i] = 0xff;
            break;
        default:
        {
        }
    }

}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    WriteCmd(0xB0 | Y);                    //设置Y位置
    WriteCmd(0x10 | ((X & 0xF0) >> 4));    //设置X位置高4位
    WriteCmd(0x00 | (X & 0x0F));            //设置X位置低4位
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++)
    {
        OLED_SetCursor(j, 0);
        for (i = 0; i < 128; i++)
        {
            WriteByte(0x00);
        }
    }
}

/**
  * @brief  OLED显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);        //设置光标位置在上半部分
    for (i = 0; i < 8; i++)
    {
        WriteByte(OLED_F8x16[Char - ' '][i]);            //显示上半部分内容
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);    //设置光标位置在下半部分
    for (i = 0; i < 8; i++)
    {
        WriteByte(OLED_F8x16[Char - ' '][i + 8]);        //显示下半部分内容
    }
}

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0' && String[i] != 0xff; i++)
    {
        OLED_ShowChar(Line, Column + i, String[i]);
    }
    OLED_SaveData(Line, String);
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
 * @brief   翻转所在行的颜色
 * @param   Line 所在行
 */
void OLED_BlackWhite_Switch(uint8_t Line)
{
    uint8_t Temp[16];
    uint8_t i, n, x;
    Cpy_Check();
    for (i = 0; Data_Category[Line - 1][i] != 0xff; i++)
    {
        if (Data_Category[Line - 1][i] == 0x00)
        {
            for (n = 0; n <= 15; n++)
            {
                Temp[n] = 0xff;
            }
        } else
        {
            for (n = 0; n <= 15; n++)
            {
                Temp[n] = ~OLED_F8x16[Data_Category[Line - 1][i] - ' '][n];
            }
        }

        OLED_SetCursor((Line - 1) * 2, i * 8);        //设置光标位置在上半部分
        for (x = 0; x < 8; x++)
        {
            WriteByte(Temp[x]);            //显示上半部分内容
        }
        OLED_SetCursor((Line - 1) * 2 + 1, i * 8);    //设置光标位置在下半部分
        for (x = 0; x < 8; x++)
        {
            WriteByte(Temp[x + 8]);        //显示下半部分内容
        }
    }

    Focus_Line = Line;
}

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
    HAL_Delay(300);
    uint32_t i, j;

    for (i = 0; i < 1000; i++)            //上电延时
    {
        for (j = 0; j < 1000; j++);
    }

    Oled_Init();            //端口初始化

    WriteCmd(0xAE);    //关闭显示

    WriteCmd(0xD5);    //设置显示时钟分频比/振荡器频率
    WriteCmd(0x80);

    WriteCmd(0xA8);    //设置多路复用率
    WriteCmd(0x3F);

    WriteCmd(0xD3);    //设置显示偏移
    WriteCmd(0x00);

    WriteCmd(0x40);    //设置显示开始行

    WriteCmd(0xA1);    //设置左右方向，0xA1正常 0xA0左右反置

    WriteCmd(0xC8);    //设置上下方向，0xC8正常 0xC0上下反置

    WriteCmd(0xDA);    //设置COM引脚硬件配置
    WriteCmd(0x12);

    WriteCmd(0x81);    //设置对比度控制
    WriteCmd(0xCF);

    WriteCmd(0xD9);    //设置预充电周期
    WriteCmd(0xF1);

    WriteCmd(0xDB);    //设置VCOMH取消选择级别
    WriteCmd(0x30);

    WriteCmd(0xA4);    //设置整个显示打开/关闭

    WriteCmd(0xA6);    //设置正常/倒转显示

    WriteCmd(0x8D);    //设置充电泵
    WriteCmd(0x14);

    WriteCmd(0xAF);    //开启显示

    OLED_Clear();                //OLED清屏
}
