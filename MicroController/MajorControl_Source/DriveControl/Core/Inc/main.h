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
#define T_Rack_Pin GPIO_PIN_0
#define T_Rack_GPIO_Port GPIOA
#define T_Roller_Pin GPIO_PIN_1
#define T_Roller_GPIO_Port GPIOA
#define T_S_CamTwo_Pin GPIO_PIN_6
#define T_S_CamTwo_GPIO_Port GPIOA
#define T_S_Roller_Rise_Pin GPIO_PIN_7
#define T_S_Roller_Rise_GPIO_Port GPIOA
#define T_S_Trans_Fold_Pin GPIO_PIN_0
#define T_S_Trans_Fold_GPIO_Port GPIOB
#define T_S_Shovel_Pin GPIO_PIN_1
#define T_S_Shovel_GPIO_Port GPIOB
#define T_Trans_Pin GPIO_PIN_10
#define T_Trans_GPIO_Port GPIOB
#define T_S_CamOne_Pin GPIO_PIN_11
#define T_S_CamOne_GPIO_Port GPIOB
#define T_FL_Pin GPIO_PIN_8
#define T_FL_GPIO_Port GPIOA
#define T_FR_Pin GPIO_PIN_9
#define T_FR_GPIO_Port GPIOA
#define T_BL_Pin GPIO_PIN_10
#define T_BL_GPIO_Port GPIOA
#define T_BR_Pin GPIO_PIN_11
#define T_BR_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
