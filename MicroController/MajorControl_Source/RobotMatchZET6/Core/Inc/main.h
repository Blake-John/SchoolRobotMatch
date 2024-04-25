/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BREncodeA_Pin GPIO_PIN_0
#define BREncodeA_GPIO_Port GPIOA
#define BREncodeB_Pin GPIO_PIN_1
#define BREncodeB_GPIO_Port GPIOA
#define IRQ_Pin GPIO_PIN_4
#define IRQ_GPIO_Port GPIOA
#define IRQ_EXTI_IRQn EXTI4_IRQn
#define CE_Pin GPIO_PIN_4
#define CE_GPIO_Port GPIOC
#define CSN_Pin GPIO_PIN_5
#define CSN_GPIO_Port GPIOC
#define RackEncodeA_Pin GPIO_PIN_9
#define RackEncodeA_GPIO_Port GPIOE
#define RackEncodeB_Pin GPIO_PIN_11
#define RackEncodeB_GPIO_Port GPIOE
#define BLEncodeA_Pin GPIO_PIN_12
#define BLEncodeA_GPIO_Port GPIOD
#define BLEncodeB_Pin GPIO_PIN_13
#define BLEncodeB_GPIO_Port GPIOD
#define MotorFR_Motivate_Pin GPIO_PIN_7
#define MotorFR_Motivate_GPIO_Port GPIOG
#define MotorFL_Motivate_Pin GPIO_PIN_8
#define MotorFL_Motivate_GPIO_Port GPIOG
#define MotorBL_Motivate_Pin GPIO_PIN_8
#define MotorBL_Motivate_GPIO_Port GPIOC
#define MotorBR_Motivate_Pin GPIO_PIN_9
#define MotorBR_Motivate_GPIO_Port GPIOC
#define Roller_Motivate_Pin GPIO_PIN_8
#define Roller_Motivate_GPIO_Port GPIOA
#define Trans_Motivate_Pin GPIO_PIN_9
#define Trans_Motivate_GPIO_Port GPIOA
#define Rack_Motivate_Pin GPIO_PIN_10
#define Rack_Motivate_GPIO_Port GPIOA
#define FLEncodeA_Pin GPIO_PIN_15
#define FLEncodeA_GPIO_Port GPIOA
#define Roller_Slave_Pin GPIO_PIN_12
#define Roller_Slave_GPIO_Port GPIOC
#define Trans_Slave_Pin GPIO_PIN_0
#define Trans_Slave_GPIO_Port GPIOD
#define Rack_Slave_Pin GPIO_PIN_1
#define Rack_Slave_GPIO_Port GPIOD
#define MotorFL_Slave_Pin GPIO_PIN_2
#define MotorFL_Slave_GPIO_Port GPIOD
#define MotorFR_Slave_Pin GPIO_PIN_3
#define MotorFR_Slave_GPIO_Port GPIOD
#define MotorBL_Slave_Pin GPIO_PIN_4
#define MotorBL_Slave_GPIO_Port GPIOD
#define MotorBR_Slave_Pin GPIO_PIN_5
#define MotorBR_Slave_GPIO_Port GPIOD
#define FLEncodeB_Pin GPIO_PIN_3
#define FLEncodeB_GPIO_Port GPIOB
#define FREncodeA_Pin GPIO_PIN_4
#define FREncodeA_GPIO_Port GPIOB
#define FREncodeB_Pin GPIO_PIN_5
#define FREncodeB_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
