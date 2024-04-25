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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nrf24.h"
#include "oled.h"
#include "menucontrol.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

unsigned char Menu_Level = 1;
unsigned char SaveData_Should_Cpy;
unsigned char Focus_Line;
unsigned char Up_Limit = 1;
unsigned char Down_Limit = 4;
uint32_t delay_250ms = 3127 * 250;
uint32_t delay_1s = 3127 * 1000;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
unsigned char Menu_State = 0x00;
unsigned char Roller_UD_Control_State = 0;
unsigned char Trans_State = 0;
unsigned char Shovel_Manual_State = 0;
unsigned char Detect_Mode_State = 0;
unsigned char Platform_Mode_State = 0;
unsigned char Boost_State = 0;
unsigned char Key_OK = 1;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    UNUSED(GPIO_Pin);
    if (Key_OK == 1)
    {


        if (GPIO_Pin == KEY3_Pin)
        {
            Menu_State = 0x05;
        }
        if (GPIO_Pin == KEY2_Pin)
        {
            Menu_State = 0x04;
        }
        if (GPIO_Pin == KEY5_Pin) // StepOut
        {
            if (Menu_Level != 1)
            {
                OLED_Clear();
                Menu_Level = 1;
                SaveData_Should_Cpy = 1;
                OLED_ShowString(1, 1, "Roller&Boost");
                OLED_ShowString(2, 1, "Trans");
                OLED_ShowString(3, 1, "Sholve");
                OLED_ShowString(4, 1, "Camera&Platform");
                Control_Init();
                Up_Limit = 1;
                Down_Limit = 4;
                if (Shovel_Manual_State == 1)
                {
                    Menu_State = 0x19;
                    Shovel_Manual_State = 0;
                } else if (Detect_Mode_State == 1)
                {
                    Menu_State = 0x20;
                    Detect_Mode_State = 0;
                } else if (Platform_Mode_State == 1)
                {
                    Menu_State = 0x2C;
                    Platform_Mode_State = 0;
                } else if (Roller_UD_Control_State == 1)
                {
                    Menu_State = 0x34;
                    Roller_UD_Control_State = 0;
                } else if(Boost_State == 1)
                {
                    Menu_State = 0x38;
                    Boost_State = 0;
                }
            }
            if (Menu_State == 1)
            {

            }
        }
        if (GPIO_Pin == KEY4_Pin) // StepIn
        {
            if (Menu_Level == 1)
            {
                switch (Focus_Line)
                {
                    case 1:
                    {
                        OLED_Clear();
                        Menu_Level = 2;
                        SaveData_Should_Cpy = 1;
                        OLED_ShowString(1, 1, "*Roller*");
                        OLED_ShowString(2, 1, "Up&Down");
                        OLED_ShowString(3,1,"Boost_Mode");
                        Up_Limit = 2;
                        Down_Limit = 3;
                        Menu_Sec_Init();
                        break;
                    }
                    case 2:
                    {
                        OLED_Clear();
                        Menu_Level = 3;
                        SaveData_Should_Cpy = 1;
                        OLED_ShowString(1, 1, "*Trans*");
                        OLED_ShowString(2, 1, "Start or Stop");
                        OLED_ShowString(3, 1, "UnFold");
                        OLED_ShowString(4, 1, "Fold");
                        Up_Limit = 2;
                        Down_Limit = 4;
                        Menu_Sec_Init();
                        break;
                    }
                    case 3:
                    {
                        OLED_Clear();
                        Menu_Level = 4;
                        SaveData_Should_Cpy = 1;
                        OLED_ShowString(1, 1, "*Sholve*");
                        OLED_ShowString(2, 1, "Manual*None*");
                        OLED_ShowString(3, 1, "Auto Once");
                        OLED_ShowString(4, 1, "Manual Switch");
                        Up_Limit = 3;
                        Down_Limit = 4;
                        Menu_Sec_Init();
                        break;
                    }
                    case 4:
                    {
                        OLED_Clear();
                        Menu_Level = 5;
                        SaveData_Should_Cpy = 1;
                        OLED_ShowString(1, 1, "*Camera*");
                        OLED_ShowString(3, 1, "Detect Mode");
                        OLED_ShowString(4, 1, "Platform");
                        Up_Limit = 3;
                        Down_Limit = 4;
                        Menu_Sec_Init();
                        break;
                    }
                    default:
                    {
                    }
                }
            } else if (Menu_Level == 2) //Roller
            {
                switch (Focus_Line)
                {
                    case 2:
                    {
                        if (Roller_UD_Control_State == 0)
                        {
                            Menu_State = 0x35;
                            Roller_UD_Control_State = 1;
                            OLED_ShowString(4, 1, "Controlling");
                        } else if (Roller_UD_Control_State == 1)
                        {
                            Menu_State = 0x34;
                            Roller_UD_Control_State = 0;
                            OLED_ShowString(4, 1, "           ");
                        }
                        break;
                    }
                    case 3:
                    {
                        if(Boost_State == 0)
                        {
                            Menu_State = 0x39;
                            Boost_State = 1;
                            OLED_ShowString(4,1,"Boosting");
                        } else if(Boost_State == 1)
                        {
                            Menu_State =0x38;
                            Boost_State = 0;
                            OLED_ShowString(4, 1, "           ");
                        }
                    }
                    default:
                    {
                    }
                }
            } else if (Menu_Level == 3) // Trans
            {
                switch (Focus_Line)
                {
                    case 2: // Start and Stop
                    {
                        if (Trans_State == 0)
                        {
                            Menu_State = 0x0D;
                            Trans_State = 1;
                            OLED_ShowString(1, 1, "*Trans*Running");
                        } else if (Trans_State == 1)
                        {
                            Menu_State = 0x0C;
                            Trans_State = 0;
                            OLED_ShowString(1, 1, "*Trans*       ");
                        }
                        break;
                    }
                    case 3: // Unfold
                    {
                        Menu_State = 0x11;
                        break;
                    }
                    case 4: // Fold
                    {
                        Menu_State = 0x10;
                        break;
                    }
                    default:
                    {
                    }
                }
            } else if (Menu_Level == 4)
            {
                switch (Focus_Line)
                {
                    case 3:
                    {
                        Menu_State = 0x15;
                        break;
                    }
                    case 4:
                    {
                        if (Shovel_Manual_State == 0)
                        {
                            Menu_State = 0x18;
                            OLED_ShowString(2, 1, "Manual*ON*    ");
                            Shovel_Manual_State = 1;
                        } else if (Shovel_Manual_State == 1)
                        {
                            Menu_State = 0x19;
                            OLED_ShowString(2, 1, "Manual*OFF* ");
                            Shovel_Manual_State = 0;
                        }
                    }
                    default:
                    {
                    }
                }
            } else if (Menu_Level == 5)
            {
                switch (Focus_Line)
                {
                    case 3:
                    {
                        if (Detect_Mode_State == 0)
                        {
                            Menu_State = 0x21;
                            OLED_ShowString(2, 1, "Detecting");
                            Detect_Mode_State = 1;
                            break;
                        } else if (Detect_Mode_State == 1)
                        {
                            Menu_State = 0x20;
                            OLED_ShowString(2, 1, "                ");
                            Detect_Mode_State = 0;
                        }
                        break;
                    }
                    case 4:
                    {
                        if (Platform_Mode_State == 0)
                        {
                            Menu_State = 0x2D;
                            OLED_ShowString(2, 1, "Platforming");
                            Platform_Mode_State = 1;
                        } else if (Platform_Mode_State == 1)
                        {
                            Menu_State = 0x2C;
                            OLED_ShowString(2, 1, "              ");
                            Platform_Mode_State = 0;
                        }
                        break;
                    }
                    default:
                    {
                    }
                }

            }
        }
        Key_OK = 0;
        HAL_TIM_Base_Start_IT(&htim4);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    Key_OK = 1;
    HAL_TIM_Base_Stop(&htim4);
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
unsigned char txbuf[32] = {0};

void ADC_To_Txbuf(uint8_t headnum, uint8_t value)
{
    txbuf[headnum] = value;
}
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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
    uint16_t ADC_Value[4];
    unsigned char i;
    unsigned char LR_MenuControl = 1;
    HAL_ADC_Init(&hadc1);
    NRF_Init();
    OLED_Init();
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_Delay(20);
    NRF_Check();
    NRF_TX_Mode();
    HAL_ADC_Start(&hadc1);
    OLED_ShowString(1, 1, "Roller&Boost");
    OLED_ShowString(2, 1, "Trans");
    OLED_ShowString(3, 1, "Sholve");
    OLED_ShowString(4, 1, "Camera&Platform");
    Control_Init();
    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        HAL_ADC_PollForConversion(&hadc1, 8);
        if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) //Get ADC
        {
            HAL_ADC_Start_DMA(&hadc1, (uint32_t *) ADC_Value, sizeof(ADC_Value) / sizeof(ADC_Value[0]));
        }

        for (i = 0; i < 4; i++) // Send ADC Value to ZET6
        {
            ADC_To_Txbuf(i, (unsigned char) (ADC_Value[i] / 256));
        }
        txbuf[31] = Menu_State;
        if (NRF_TX_Packet(txbuf) == 0x20) //Send, and if Received ACK
        {
            Menu_State = 0;
        }
        HAL_Delay(20);

//        Menu Control
        if (Shovel_Manual_State == 0 && Platform_Mode_State == 0 && Roller_UD_Control_State == 0 && Boost_State == 0)
        {
            if (LR_MenuControl == 1)
            {
                if (ADC_Value[2] > 3000)
                {
                    Control_Up();
                    while (delay_250ms--);
                    delay_250ms = 3127 * 250;
                }
                if (ADC_Value[2] < 300)
                {
                    Control_Down();
                    while (delay_250ms--);
                    delay_250ms = 3127 * 250;
                }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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