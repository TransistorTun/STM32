/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_i2c.h"
#include "ROTARY_ENCODER.h"
#include "BUTTON.h"
#include "DHT11.h"
#include "DS3231.h"
#include "HCSR04.h"

#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
BUTTON_HandleTypeDef button_1;
LCD_I2C_HandleTypeDef lcd_1;
RE_HandleTypeDef re_1;
DS3231_Time DS3231_1;
DHT11_HandleTypeDef dht_1;
SR04_HandleTypeDef sr04_1;

char MODE1[] = "MODE1: TEMP & HUMID";
char MODE2[] = "MODE2: DISTANCE";
char MODE3[] = "MODE3: DIGITAL CLOCK";
char MODE4[] = "MODE4: RESET TIME";

static uint8_t condition = 0;
static uint16_t click = 0;
static uint8_t start = 1;
static uint32_t time_waiting = 0;

//Display
static char data_distance[5];
static char data_temp[6];
static char data_humi[6];
static char time [20];

//HCSR04
static uint8_t distance = 0;

//DHT11
static float temperature = 0;
static float humidity = 0;

enum MODE_t
{
  MODE_DHT = 1,
  MODE_SR04 = 2,
  MODE_CLOCK = 3,
  MODE_SETTIME = 4
};

static uint8_t mode = MODE_DHT;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void BUTTON_Pressing_Callback(BUTTON_HandleTypeDef *ButtonX)
{
  condition = !condition;
}

void Display_Menu ()
{
  lcd_set_cursor(&lcd_1, 0, 0);
	lcd_send_string(&lcd_1, MODE1);
	lcd_set_cursor(&lcd_1, 0, 1);
	lcd_send_string(&lcd_1, MODE2);
	lcd_set_cursor(&lcd_1, 0, 2);
	lcd_send_string(&lcd_1, MODE3);
	lcd_set_cursor(&lcd_1, 0, 3);
	lcd_send_string(&lcd_1, MODE4); 
}

void MODE_Handle ()
{
  if (condition)
  {
    switch (mode)
    {
    case MODE_DHT:
      if (start)
      {
        lcd_clear(&lcd_1);
      }
      start = 0;
      if (HAL_GetTick() - time_waiting >= 500)
      {
        DHT_Read_Temperature_Humidity(&dht_1);
        temperature = dht_1.Temp;
        humidity = dht_1.Hum;
        lcd_set_cursor(&lcd_1, 0, 0);
        sprintf(data_temp, "Tempe: %.2f C", temperature);

        lcd_set_cursor(&lcd_1, 0, 1);
        sprintf(data_humi, "Hum: %.2f %%", humidity);
        time_waiting = HAL_GetTick();
      }
      
      break;
    
    case MODE_SR04:
      if (start)
      {
        lcd_clear(&lcd_1);
      }
      start = 0;
      if (HAL_GetTick() - time_waiting >= 500)
      {
        distance = HCSR04_Get_Distance(&sr04_1);
        lcd_set_cursor(&lcd_1, 0, 0);
        sprintf(data_distance, "DISTANCE: %2d", distance);
        lcd_send_string(&lcd_1, data_distance);
        time_waiting = HAL_GetTick();
      }
      break;

    case MODE_CLOCK:
    if (start)
      {
        lcd_clear(&lcd_1);
      }
    start = 0;
    if (HAL_GetTick() - time_waiting >= 500)
    {
      DS3231_GetTime(&DS3231_1);
      DS3231_GetDate(&DS3231_1);
      HAL_Delay(200);

      lcd_set_cursor(&lcd_1, 0, 0);
      lcd_send_string(&lcd_1, "HELLO PhamTuan!");
      sprintf(time, "%02d:%02d:%02d", DS3231_1.Hour, DS3231_1.Min, DS3231_1.Sec);
      lcd_set_cursor(&lcd_1, 0, 1);
      lcd_send_string(&lcd_1, time);
      sprintf(time, "Thu%2d  %02d-%02d-20%02d",DS3231_1.Day, DS3231_1.Date, DS3231_1.Month, DS3231_1.Year);
      lcd_set_cursor(&lcd_1, 0, 2);
      lcd_send_string(&lcd_1, time);
      lcd_set_cursor(&lcd_1, 0, 3);
      lcd_send_string(&lcd_1, "HAVE A NICE DAY!");
      HAL_Delay(200);
    }
    
      break;

    case MODE_SETTIME:

      break;

    default:
      break;
    }
  }

  else
  {
    RE_Get_Value(&re_1);
    click = re_1.current_position % 4;
    if (click == 1)   //BLINK MODE1
    { 
      Display_Menu();
	    HAL_Delay(1000);
	    lcd_clear(&lcd_1);
	    lcd_set_cursor(&lcd_1, 0, 1);
	    lcd_send_string(&lcd_1, MODE2);
	    lcd_set_cursor(&lcd_1, 0, 2);
	    lcd_send_string(&lcd_1, MODE3);
	    lcd_set_cursor(&lcd_1, 0, 3);
	    lcd_send_string(&lcd_1, MODE4);
	    HAL_Delay(1000);
	    lcd_set_cursor(&lcd_1, 0, 0);
	    lcd_send_string(&lcd_1, MODE1);
      start = 1;
    }
    
    if (click == 2)  //BLINK MODE2
    {
      Display_Menu();
      HAL_Delay(1000);
      lcd_clear(&lcd_1);
      lcd_set_cursor(&lcd_1, 0, 0);
      lcd_send_string(&lcd_1, MODE1);
      lcd_set_cursor(&lcd_1, 0, 2);
      lcd_send_string(&lcd_1, MODE3);
      lcd_set_cursor(&lcd_1, 0, 3);
      lcd_send_string(&lcd_1, MODE4);
      HAL_Delay(1000);
      lcd_set_cursor(&lcd_1, 0, 1);
      lcd_send_string(&lcd_1, MODE2);
      start = 1;
    }
    
    if (click == 3)  //BLINK MODE3
    {
      Display_Menu();
      HAL_Delay(1000);
      lcd_clear(&lcd_1);
      lcd_set_cursor(&lcd_1, 0, 0);
      lcd_send_string(&lcd_1, MODE1);
      lcd_set_cursor(&lcd_1, 0, 1);
      lcd_send_string(&lcd_1, MODE2);
      lcd_set_cursor(&lcd_1, 0, 3);
      lcd_send_string(&lcd_1, MODE4);
      HAL_Delay(1000);
      lcd_set_cursor(&lcd_1, 0, 2);
      lcd_send_string(&lcd_1, MODE3);
      start = 1;
    }
    
    if (click == 0) //BLINK MODE4
    {
      Display_Menu();
      HAL_Delay(1000);
      lcd_clear(&lcd_1);
      lcd_set_cursor(&lcd_1, 0, 0);
      lcd_send_string(&lcd_1, MODE1);
      lcd_set_cursor(&lcd_1, 0, 1);
      lcd_send_string(&lcd_1, MODE2);
      lcd_set_cursor(&lcd_1, 0, 2);
      lcd_send_string(&lcd_1, MODE3);
      HAL_Delay(1000);
      lcd_set_cursor(&lcd_1, 0, 3);
      lcd_send_string(&lcd_1, MODE4);
      start = 1;
    }
    

  }
  
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
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start(&htim3);
  lcd_i2c_init(&lcd_1, &hi2c1, 20, 4, 0x27<<1);
  RE_Init(&re_1, &htim2);
  DS3231_Init(&DS3231_1, &hi2c2);
  DHT11_Init(&dht_1, &htim3, GPIOA, GPIO_PIN_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

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
