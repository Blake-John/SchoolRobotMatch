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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motorcontrol.h"
#include "action_usart.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//UART.c
unsigned char UART2_Rx_Buf[5] = {0}; //USART1存储接收数据
unsigned int UART2_Rx_cnt = 0;                   //USART1接受数据计数
uint8_t UART2_temp[1] = {0};       //USART2接收数据缓存
uint8_t Rx_buf[15] = {0};
uint8_t Detect_Rx_buf[52] = {0};
unsigned char i = 0;
unsigned char Execute_Order = 0;
uint16_t Motor_Side = 0;
uint16_t Motor_Speed = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
unsigned char USART_State = 1;
unsigned char Rx_cnt = 0;
unsigned char Menu_Sign = 0;
// Fix it to 0
unsigned char Detect_State = 0;
unsigned char Receive_State = 0;
unsigned char Detect_Flag = 0;
unsigned char p = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //USART中断函数
{
    if (huart->Instance == USART2)
    {
        if (Detect_State == 0)
        {
            if (USART_State == 2)
            {
                if (Rx_cnt <= 8)
                {
                    Rx_buf[Rx_cnt] = UART2_temp[0];
                    Rx_cnt++;
                    if (Rx_cnt > 8)
                    {
                        USART_State = 1;
                        Rx_cnt = 0;
                    }
                }
            }
        } else if (Detect_State == 1)
        {
            if (UART2_temp[0] == '@' && Detect_Flag != 1)
            {
                Receive_State = 1;
                p = 0;
            } else if (Receive_State == 1)
            {
                if (UART2_temp[0] != '\n' && UART2_temp[0] != '\t')
                {
                    Detect_Rx_buf[p] = UART2_temp[0];
                    p++;
                } else
                {
                    if (UART2_temp[0] == '\n')
                    {
                        Detect_Rx_buf[p] = '\0';
                        Receive_State = 0;
                        p = 0;
                        Detect_Flag = 1;
                    } else if (UART2_temp[0] == '\t')
                    {
                        Detect_State = 0;
                    }
                }
            }
        }
    }
    HAL_UART_Receive_IT(&huart2, (uint8_t *) UART2_temp, 1);
}

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
    uint32_t delay_2s = 3127 * 2000;
    while (delay_2s--);
    HAL_UART_Init(&huart2);
    Motor_Init();
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RACK_MOTOR_COMPARE);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, ROLLER_MOTOR_COMPARE_SLOW);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, TRANS_MOTOR_COMPARE);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 145);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ROLLER_INITIAL_COMPARE);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, SHOVEL_INITIAL_COMPARE);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Trans_UNFOLD_COMPARE);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, SUSTAINER_LEFT_UP_COMPARE);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, SUSTAINER_RIGHT_UP_COMPARE);
    HAL_Delay(20);
    unsigned char Aquire_Sign = 0xB2;
    uint16_t duty1 = 100, duty2 = 145;
    uint32_t px = 0, py = 0;
    float dx = 0, dy = 0;
    HAL_UART_Receive_IT(&huart2, (uint8_t *) UART2_temp, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        if (Detect_State == 0)
        {
            USART_State = 2;
            HAL_UART_Transmit(&huart2, (uint8_t *) &Aquire_Sign, 1, 0xff);
            while (USART_State == 2);
            Menu_Sign = Rx_buf[8];
            Menu_Action(Menu_Sign);
            PID_Motor_Action(Rx_buf);
            HAL_Delay(3);
        } else if (Detect_State == 1)
        {
            if (Detect_Flag == 1)
            {

                // get the angle from the string
                char *ptr;
                dx = strtof(((const char *) Detect_Rx_buf + 1), &ptr);
                dy = strtof((ptr + 1), NULL);
                // calculate the duty by the angle
                int32_t duty_dx, duty_dy;
                duty_dx = (int) (dx / 0.9f);
                duty_dy = (int) (dy / 0.9f);
                duty1 += (int) duty_dx;
                duty2 += (int) duty_dy;
                __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, duty2);
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty1);
                Detect_Flag = 0;
            }
        }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
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
