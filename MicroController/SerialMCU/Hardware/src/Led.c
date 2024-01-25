#include "Led.h"



/**
 * @brief Initialize the LED by the given RCC_APB2Periph, GPIOx, GPIO_Pin and GPIO_Speed
 * 
 * @param RCC_APB2Periph specifies the APB2 peripheral to gates its clock.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bit to be written. This parameter can be one of GPIO_Pin_x where x can be (0..15).
 * @param GPIO_Speed specifies the speed for the selected pins.
 */
void LedInit (uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed;

    GPIO_Init (GPIOx, &GPIO_InitStruct);
}


/**
 * @brief Turn the specific LED to be ON or OFF
 * 
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bit to be written. This parameter can be one of GPIO_Pin_x where x can be (0..15).
 * @param states the LED state, which can be ON or OFF. See @ref #LedAction
 */
void LedTurn (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, LedAction state)
{
    GPIO_WriteBit (GPIOx, GPIO_Pin, state);
}
