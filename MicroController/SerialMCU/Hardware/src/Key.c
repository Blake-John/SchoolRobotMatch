#include "Key.h"



/**
 * @brief Initialize the KEY by the given RCC_APB2Periph, GPIOx, GPIO_Mode, GPIO_Pin
 * 
 * @param RCC_APB2Periph specifies the APB2 peripheral to gates its clock.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Mode Specifies the operating mode for the selected pins.
 * @param GPIO_Pin specifies the GPIO pins to be configured.
 */
void KeyInit (uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIOx, &GPIO_InitStruct);
}



/**
 * @brief judge wheter the specific key is pressed
 * 
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin the target pin
 * @param GPIO_Mode the input mode of the key
 * @return returns 1 if key is pressed, else 0
 */
uint8_t GetKey (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
    if (GPIO_Mode == GPIO_Mode_IPU)
    {
        if (GPIO_ReadInputDataBit (GPIOx, GPIO_Pin) == 0)
        {
            Delay_ms (20);
            while (GPIO_ReadInputDataBit (GPIOx, GPIO_Pin) == 0);
            Delay_ms (20);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (GPIO_Mode == GPIO_Mode_IPD)
    {
        if (GPIO_ReadInputDataBit (GPIOx, GPIO_Pin))
        {
            Delay_ms (20);
            while (GPIO_ReadInputDataBit (GPIOx, GPIO_Pin) == 1);
            Delay_ms (20);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}
