/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motorcontrol.h"
#include "nrf24l01.h"
#include "encode.h"
#include "servocontrol.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */



/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
unsigned char Shovel_Manual_State = 0;
unsigned char Detect_Mode_State = 0;
unsigned char Platform_Mode_State = 0;
unsigned char NRF_Rxbuf[32] = {0};
unsigned char Menu_State = 0x00;
unsigned char Slave_Send_State = 0x00;
uint8_t UART_Rxbuf[1] = {0};
extern Motor MotorFL, MotorFR, MotorBL, MotorBR;
extern Motor_Rack Rack;
uint8_t PIDCalculate_State = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == IRQ_Pin)
    {
        NRF_RX_Packet(NRF_Rxbuf);
    }
}

float Speed_Resize_L(uint8_t State)
{
    switch (State)
    {
        case 0:
        case 1:
        case 15:
        case 16:
        case 2:
        case 13:
        case 14:
            return 6;
        case 3:
        case 11:
        case 12:
            return 2;
        case 4:
        case 5:
        case 9:
        case 10:
            return (float) 0.6;
        default:
            return 0;
    }
}

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_SPI1_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_TIM6_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    /* USER CODE BEGIN 2 */
    unsigned char State_L_UD, State_L_LR, State_R_UD, State_R_LR = 0;
    unsigned char Roller_Realtime_Control = 0;
    unsigned char Boost_State = 0;
    NRF_Init();
    HAL_UART_Init(&huart1);
    HAL_UART_Init(&huart2);
    Motor_Init();
    HAL_Delay(20);
    NRF_Check();
    NRF_RX_Mode();
    HAL_UART_Receive_IT(&huart1, (uint8_t *) UART_Rxbuf, 1);
    MotorEncode_Init();
    HAL_Delay(100);
//    HAL_UART_Transmit(&huart1,&Reset_Sign,1,0xff);
//    HAL_UART_Transmit(&huart1,&Reset_Sign,1,0xff);
//    HAL_UART_Transmit(&huart1,&Reset_Sign,1,0xff);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        State_L_LR = NRF_Rxbuf[0];
        State_L_UD = NRF_Rxbuf[1];
        State_R_UD = NRF_Rxbuf[2];
        State_R_LR = NRF_Rxbuf[3];
        Menu_State = NRF_Rxbuf[31];
        switch (Menu_State)
        {
            case 0x18:
            {
                Shovel_Manual_State = 1;
                break;
            }
            case 0x19:
            {
                Shovel_Manual_State = 0;
                break;
            }
            case 0x20:
            {
                Detect_Mode_State = 0;
                break;
            }
            case 0x21:
            {
                Detect_Mode_State = 1;
                break;
            }
            case 0x2C:
            {
                Slave_Send_State = 0x2C;
                Platform_Mode_State = 0;
                break;
            }
            case 0x2D:
            {
                Platform_Mode_State = 1;
                break;
            }
            case 0x34:
            {
                Roller_Realtime_Control = 0;
                break;
            }
            case 0x35:
            {
                Roller_Realtime_Control = 1;
                break;
            }
            case 0x0C:
            {
                Trans_Seize();
                break;
            }
            case 0x0D:
            {
                Trans_Run();
                break;
            }
            case 0x38:
            {
                Slave_Send_State = 0x38;
                Boost_State = 0;
                break;
            }
            case 0x39:
            {
                Slave_Send_State = 0x39;
                Boost_State = 1;
                break;
            }
            default:
            {
            }

        }
        if (State_L_LR != 0 && State_L_UD != 0)
        {
            if (State_L_UD >= 9 && State_L_LR <= 8 && State_L_LR >= 6)
            {
                Car_Forward();
                Set_Target_Speed(Speed_Resize_L(State_L_UD));
            } else if (State_L_UD <= 5 && State_L_LR <= 8 && State_L_LR >= 6)
            {
                Car_Backward();
                Set_Target_Speed(Speed_Resize_L(State_L_UD));
            } else if (State_L_UD <= 8 && State_L_UD >= 6 && State_L_LR <= 8 && State_L_LR >= 6 && State_R_LR >= 5 &&
                       State_R_LR <= 8)
            {
                Car_Seize();
                Set_Target_Speed(0);
            } else if (State_L_UD <= 8 && State_L_UD >= 6 && State_L_LR <= 5)
            {
                Car_Leftward();
                Set_Target_Speed((float )0.6);
            } else if (State_L_UD <= 8 && State_L_UD >= 6 && State_L_LR >= 9)
            {
                Car_Rightward();
                Set_Target_Speed((float )0.6);
            } else if (Shovel_Manual_State == 0 && Platform_Mode_State == 0)
            {
                if (State_R_LR <= 3)
                {
                    Car_Counter_Clockwise();
                    Set_Target_Speed((float )0.6
                    );
                } else if (State_R_LR >= 13)
                {
                    Car_Clockwise();
                    Set_Target_Speed((float )0.6);
                }
            }
        }
        if (Shovel_Manual_State == 1)
        {
            if (State_R_LR <= 3)
            {
                Rack_Backward();
            } else if (State_R_LR >= 13)
            {
                Rack_Forward();
            } else if (State_R_LR >= 4 && State_R_LR <= 12 && State_R_UD >= 4 && State_R_UD <= 12)
            {
                Rack_Seize();
            } else if (State_R_UD <= 3)
            {
                Slave_Send_State = 0x24;
            } else if (State_R_UD >= 13)
            {
                Slave_Send_State = 0x25;
            }
        }

        if (Platform_Mode_State == 1)
        {
            if (State_R_LR <= 3)
            {
                Sustainer_Down();
            } else if (State_R_LR >= 13)
            {
                Sustainer_Up();
            } else if (State_R_UD <= 3)
            {
                Roller_Down();
            } else if (State_R_UD >= 13)
            {
                Roller_Up();
            }
        }

        if (Detect_Mode_State == 1)
        {
            Slave_Send_State = 0x21;
        }

        if (Menu_State == 0x05)
        {
            Roller_Forward();

        } else if (Menu_State == 0x04)
        {
            Roller_Seize();
        }
        if (Roller_Realtime_Control == 1 || Boost_State == 1)
        {
            if (State_R_UD >= 13)
            {
                Slave_Send_State = 0x31;
            } else if (State_R_UD <= 4)
            {
                Slave_Send_State = 0x30;
            }
        }

        if (PIDCalculate_State == 1 && Boost_State != 1)
        {
            PID_Calculate(&MotorFL);
            PID_Calculate(&MotorFR);
            PID_Calculate(&MotorBL);
            PID_Calculate(&MotorBR);
            PIDCalculate_State = 0;
        }

/* USER CODE END WHILE */

/* USER CODE BEGIN 3 */
    }

}
/* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
