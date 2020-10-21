/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 8

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
uint16_t adc_values[2];
uint32_t values[8], avg_values[10];
uint32_t movingAverage, movingAverageSum;
uint32_t zero_current;
int8_t rev = 1;
uint8_t cycle = 0;
uint8_t samples = 0;
uint32_t x = 0;
uint8_t data[16];
uint8_t state = 0, last_state = 0;
float ref;
float last_ref = 0;
//uint32_t m_nStart;               //DEBUG Stopwatch start cycle counter value
//uint32_t m_nStop;
float ref = 0;

struct PID_Data{
	uint8_t run;
	float Kp;
	float Ti;
	float Td;
	float Ts;
	float Kb;
	float output_rate;

	float P;
	float I;
	float D;

	float reference;
	float input;
	float input_raw;
	float error;
	float error_dz;
	float last_error;
	float output_sat;
	float output;
	float last_output;

	float input_offset;
	float output_min;
	float output_max;
	float error_deadzone;
	float antiwindup_correction;
	float output_offset;
};

struct PID_Data regulator;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM4_Init(void);
static void MX_DMA_Init(void);
/* USER CODE BEGIN PFP */
void PID_Init (struct PID_Data *pid, float P, float I, float D, float Kb, float Ts, float rate, float deadzone, float min, float max, float output_offset, float input_offset);
void PID_Controller (struct PID_Data *pid);
void PID_TurnOn (struct PID_Data *pid);
void PID_TurnOff (struct PID_Data *pid);
uint8_t PID_Running (struct PID_Data *pid);

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
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_DMA_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  HAL_TIM_PWM_Init(&htim1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

  TIM1 -> CCR1 = 7200;

  HAL_ADC_Start_DMA(&hadc1, &adc_values[0], 2);

  while(cycle < 8);
  cycle = 0;
  movingAverageSum = 0;
  for(uint8_t i = 0; i < 8; i++){
  	movingAverageSum += values[i];
  }
  movingAverage = movingAverageSum >> 3;
  zero_current = movingAverage;
  PID_Init(&regulator, 2.0, 8.0, 0.0, 8.0, 0.001, 0.0, 5.0, 720.0, 13680.0, 7200.0, (float)zero_current);
  regulator.input_raw = (float)zero_current;
  PID_TurnOn(&regulator);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(cycle == 8){
		  cycle = 0;
		  movingAverageSum = 0;
		  for(uint8_t i = 0; i < 8; i++){
			  movingAverageSum += values[i];
		  }
		  avg_values[samples] = movingAverageSum >> 3;
		  samples++;
	  }

	  if(samples == 10){
		  samples = 0;
		  movingAverageSum = 0;
		  for(uint8_t i = 0; i < 10; i++){
		  	movingAverageSum += avg_values[i];
		  }
		  regulator.input_raw = (float)(movingAverageSum / 10);

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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1|RCC_PERIPHCLK_ADC12
                              |RCC_PERIPHCLK_TIM34;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV4;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_PLLCLK;
  PeriphClkInit.Tim34ClockSelection = RCC_TIM34CLK_PLLCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the ADC multi-mode 
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 14400 - 1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 100;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 900 - 1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&htim4, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	rev *= -1;
}

void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* hadc){
	values[cycle] = adc_values[0];
	cycle++;
	if(adc_values[1] > 65) ref = ((float)(adc_values[1] >> 1) * rev);
	else ref = 0.0;
}

void HAL_SYSTICK_Callback (void){
	switch (state){
		case 0:
			if((last_ref > -1.0 && last_ref < 1.0) && last_ref != ref){
				//TIM1 -> CCR1 = 7200 + 1000 * rev;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				regulator.reference = 1024.0 * rev;
				state++;
			}else{
				regulator.reference = 0.0;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			}
			break;

		case 1:
			x++;
			if( x >= 50){
				regulator.reference -= ((1024.0 - ref) / 100.0);
			}
			if(x == 150){
				x = 0;
				state++;
				regulator.reference = ref;
			}
			break;

		case 2:
			regulator.reference = ref;
			if((ref > -1.0 && ref < 1.0) && (last_ref != ref)){
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
				state = 0;
			}
			break;
	}
	PID_Controller(&regulator);
	TIM1 -> CCR1 = (uint32_t)regulator.output;
	last_ref = ref;
	last_state = state;
	samples = 0;
}

/**
  * @brief  Inicjalizacja parametrów regulatora.
  *
  * @note   Funckcja służy do inicjalizacji parametrów reguatroa
  *
  *
  *
  * @param  pid - wskaźnik na strukturę przechowującą wartości związane z regulatorem
  * @param  P - wzmocnienie członu P
  * @param  I - wzmocnienie członu I
  * @param 	D - wzmocnienie członu D
  * @param  Kb - wzmocnienie członu antiwindup
  * @param 	Ts - czas próbkowania
  * @param 	rate - maksymalny przyrost wyjścia
  * @param 	deadzone - martwa strefa uchybu
  * @param 	min - minimalna wartośc wyjścia
  * @param 	max - maksymalna wartość wyjścia
  * @param 	output_offset - offset wyjścia
  * @param 	input_offset - offset wejścia
  *
  * @retval None
  */
void PID_Init (struct PID_Data *pid, float P, float I, float D, float Kb, float Ts, float rate, float deadzone, float min, float max, float output_offset, float input_offset){
	pid -> Kp = P;
	pid -> Ti = I;
	pid -> Td = D;
	pid -> Ts = Ts;
	pid -> output_min = min;
	pid -> output_max = max;
	pid -> Kb = Kb;
	pid -> output_offset = output_offset;
	pid -> input_offset = input_offset;
	pid -> output_rate = rate;
	pid -> error_deadzone = deadzone;
}

void PID_Controller (struct PID_Data *pid){
	if(pid->run){
		//Obliczenie uchybu sterowania
		if(pid->reference == 0){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			pid->I = 0;
		}
		else{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		}
		pid->input = pid->input_raw - pid->input_offset;
		pid->error_dz = pid->reference - (pid->input);

		if(pid->error_deadzone){
			if((pid->error_dz < pid->error_deadzone) && (pid->error_dz > -pid->error_deadzone)){
				pid->error = 0.0;
			}else pid->error = pid->error_dz;
		}

		pid->P = pid->Kp * pid->error;

		if(pid->Ti){
			pid->I += (pid->error + pid->antiwindup_correction)*pid->Ts/pid->Ti;
		}else{
			pid->I = 0;
		}

		if(pid->Td) pid->D = (pid->Td/pid->Ts) * (pid->error_dz - pid->last_error);

		//obliczenie wyjścia
		pid->output_sat = pid->P + pid->I + pid->D;

		//Ograniczenie szybkości narastania wyjścia
		if(pid->output_rate){
			if((pid->output_sat - pid->last_output) > pid->output_rate) pid->output_sat = pid->last_output + pid->output_rate;
			else if((pid->output_sat - pid->last_output) < -pid->output_rate) pid->output_sat = pid->last_output - pid->output_rate;
		}
	}else{
		pid->output_sat = 0;
	}
	//Dodanie przesunięcia do wyjścia
	pid -> output_sat += pid -> output_offset;

	//Saturacja wyjścia, jeśli istnieją ograniczenia
	if(pid->output_sat < pid->output_min) pid->output = pid->output_min;
	else if(pid->output_sat > pid->output_max) pid->output = pid->output_max;
	else pid->output = pid->output_sat;

	//Zapamiętanie poprzednich wartości
	pid->antiwindup_correction = pid->Kb * (pid->output - pid->output_sat);
	pid->last_error = pid->error_dz;
	pid->last_output = pid->output;

}

void PID_TurnOn (struct PID_Data *pid){
	pid->run = 1;
}

void PID_TurnOff (struct PID_Data *pid){
	pid->D = 0;
	pid->I = 0;
	pid->antiwindup_correction = 0;
	pid->error = 0;
	pid->error_dz = 0;
	pid->last_error = 0;
	pid->reference = 0;
	pid->output_sat = 0;
	pid->output = pid->output_offset;
	pid->last_output = 0;
	pid->run = 0;
}

uint8_t PID_Running (struct PID_Data *pid){
	return pid->run;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
