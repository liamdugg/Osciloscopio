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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX		200

#define ATEN_03		6	//A0
#define ATEN_05		7	//A1
#define AMP_1		0	//A2
#define AMP_3		1	//A3
#define AMP_5		2	//A4
#define AMP_10		3	//A5
#define AMP_31		4	//A6
#define AMP_50		5	//A7
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;

/* USER CODE BEGIN PV */
int flag;
char adc_char[10];
int trigger_point = 1;
int trigger_level = 2048;
int contador;

uint32_t buffer_adc[MAX];
uint32_t buffer_display[MAX];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM5_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */

void int_to_char(uint32_t num, char texto[]){

	uint32_t buffer = num;
	int contador = 0;

	while(buffer > 0){
		buffer /= 10;
		contador++;
	}

	texto[contador] = '\0';

	buffer = num;
	int pos = contador - 1, digito;
	while(pos >= 0){
		digito = buffer%10;
		buffer /= 10;
		texto[pos] = digito + '0';
		pos--;
	}
}

float map(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void actualizar_escala()
{
switch(contador)
	{
		case AMP_1://A2
			ssd1306_SetCursor(115, 55);
			ssd1306_WriteString("x1", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("1,6", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-1,6", Font_6x8, White);
		break;
		case AMP_3://A3
			ssd1306_SetCursor(115, 55);
			ssd1306_WriteString("x3", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("0,6", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-0,6", Font_6x8, White);
		break;
		case AMP_5://A4
			ssd1306_SetCursor(115, 55);
			ssd1306_WriteString("x5", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("0,3", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-0,3", Font_6x8, White);
		break;
		case AMP_10://A5
			ssd1306_SetCursor(109, 55);
			ssd1306_WriteString("x10", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("0,1", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-0,1", Font_6x8, White);
		break;
		case AMP_31://A6
			ssd1306_SetCursor(109, 55);
			ssd1306_WriteString("x31", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("52m", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-52m", Font_6x8, White);
		break;
		case AMP_50://A7
			ssd1306_SetCursor(109, 55);
			ssd1306_WriteString("x50", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("33m", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-33m", Font_6x8, White);
		break;
		case ATEN_03://A0
			ssd1306_SetCursor(109, 55);
			ssd1306_WriteString("x.3", Font_6x8, White);
			ssd1306_SetCursor(17, 9);
			ssd1306_WriteString("6", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(11, 56);
			ssd1306_WriteString("-6", Font_6x8, White);
		break;
		case ATEN_05://A1
			ssd1306_SetCursor(109, 55);
			ssd1306_WriteString("x.5", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("3,3", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-3,3", Font_6x8, White);
		break;
		default://A2
			ssd1306_SetCursor(115, 55);
			ssd1306_WriteString("x1", Font_6x8, White);
			ssd1306_SetCursor(6, 9);
			ssd1306_WriteString("1,6", Font_6x8, White);
			ssd1306_SetCursor(17, 33);
			ssd1306_WriteString("0", Font_6x8, White);
			ssd1306_SetCursor(0, 56);
			ssd1306_WriteString("-1,6", Font_6x8, White);
		break;
	}
}

void display_plot_grilla(void){

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);

	ssd1306_VLine(26, 9, 55, White);   // left vartical line
	ssd1306_VLine(127, 9, 3, White);   // right vrtical line up
	ssd1306_VLine(127, 60, 3, White);  // right vrtical line bottom

	ssd1306_HLine(24, 9, 7, White);    // Max value auxiliary mark
	ssd1306_HLine(24, 36, 2, White);
	ssd1306_HLine(24, 63, 7, White);

	ssd1306_HLine(51, 9, 3, White);    // Max value auxiliary mark
	ssd1306_HLine(51, 63, 3, White);

	ssd1306_HLine(76, 9, 3, White);    // Max value auxiliary mark
	ssd1306_HLine(76, 63, 3, White);

	ssd1306_HLine(101, 9, 3, White);   // Max value auxiliary mark
	ssd1306_HLine(101, 63, 3, White);

	ssd1306_HLine(123, 9, 5, White);   // right side Max value auxiliary mark
	ssd1306_HLine(123, 63, 5, White);

	for (int x = 26; x <= 128; x += 5){
	  ssd1306_HLine(x, 36, 2, White);  // Draw the center line (horizontal line) with a dotted line
	}

	for (int x = (127 - 25); x > 30; x -= 25){
		for (int y = 10; y < 63; y += 5){
			ssd1306_VLine(x, y, 2, White); // Draw 3 vertical lines with dotted lines
		}
	}
	ssd1306_SetCursor(14, 0);
	ssd1306_WriteString("XX.XKH rmsX.XV XXuS", Font_6x8, White);
	//
}

/*
void Analizar_amplitud(uint32_t *buffer)
{
	uint32_t Valor_max;

	for(int i = 1; i< MAX; i++)
	{
		if(buffer[i] > buffer[i-1])
			Valor_max = buffer[i];
	}
	if(Valor_max < 2088)
		Cambiar_MUX(AMP_50);
	else if(Valor_max>2088 && Valor_max<2112)
		Cambiar_MUX(AMP_31);
	else if(Valor_max>2112 && Valor_max<2252)
		Cambiar_MUX(AMP_10);
	else if(Valor_max>2252 && Valor_max<2457)
		Cambiar_MUX(AMP_5);
	else if(Valor_max>2457 && Valor_max<2699)
		Cambiar_MUX(AMP_3);
	else if(Valor_max>2699)
		Cambiar_MUX(AMP_1);
}
*/

void display_plot_signal(void){

	int y3 = 0, y4 = 0;
	int x3 = 0, x4 = 0;

	if(flag == 1)
	{
		//ssd1306_Fill(Black);
		trigger_point = 1;

		for(int i = 0; i<MAX; i++)
				buffer_display[i] = buffer_adc[i];

		//Analizar_amplitud(buffer_display);
		for(int i = 0; i <= 98; i++)
		{
			// flanco descendente
			if((buffer_display[i] > trigger_level ) && (buffer_display[i+1]) < trigger_level )
			{
				trigger_point = i;
				break;
			}
		}

		for (int k = 0; k <= 98; k++){

			x3 = k + trigger_point;
			x4 = x3 + 1;

			y3 = map(buffer_display[x3], 0, 4095, 63, 9); 				// convert to plot
			y4 = map(buffer_display[x4], 0, 4095, 63, 9);

			ssd1306_Line(k + 27, y3, k + 28, y4, White);
		 }
		flag = 0;
		HAL_ADC_Start_DMA(&hadc1, buffer_adc, MAX);
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	//trigger_level += 300;
	//if(trigger_level > 3800)
		//trigger_level = 100;
	contador++;
	contador %= 8;
	switch(contador)
	{
		case AMP_1://A2
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_RESET);

		break;
		case AMP_3://A3
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_RESET);
		break;
		case AMP_5://A4
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_SET);
		break;
		case AMP_10://A5
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_SET);
		break;
		case AMP_31://A6
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_SET);
		break;
		case AMP_50://A7
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_SET);
		break;
		case ATEN_03://A0
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_RESET);
		break;
		case ATEN_05://A1
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_RESET);
		break;
		default://A2
			HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_RESET);
		break;
	}
}

void display_plot_trigger(void){

	int trigger_actual = 0;

	trigger_actual = map(trigger_level, 0, 4095, 63, 9);

	//ssd1306_HLine(26, trigger_actual, 100, White);

	// dibujo el triangulo
	ssd1306_VLine(127, trigger_actual-2, 4, White);
	ssd1306_VLine(126, trigger_actual-1, 2, White);
	ssd1306_DrawPixel(125, trigger_actual, White);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
		flag = 1;
}


/*
void RMS(void)
{
	#include <math.h>
	for(int i=0; i<NS; i++){
		adc1 = (float32_t)adc_buffer[i]*3.3/4096.0;
		valorMax = adc1*adc1+valorMax;
	}
	pResultado = sqrt(valorMax / (float32_t) blockSize);
	valorMax = 0;
}
*/

/* ------------------------ Tareas Free RTOS ------------------------ */

void Init_Sistema(void *pvParameters){

	ssd1306_Init();
	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim3);
	HAL_ADC_Start_DMA(&hadc1, buffer_adc, MAX);
	HAL_GPIO_WritePin(MUX_SEL0_GPIO_Port, MUX_SEL0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MUX_SEL2_GPIO_Port, MUX_SEL2_Pin, GPIO_PIN_RESET);
	vTaskDelete(NULL);
}
void Mostrar_pantalla(void *pvParameters){

	while(1){
		display_plot_grilla();
		display_plot_signal();
		display_plot_trigger();
		actualizar_escala();
		ssd1306_UpdateScreen();
		vTaskDelay(17/portTICK_RATE_MS);
	}
}

void Cambiar_Modo(void *pvParameters){

}

void Enviar_USB(void *pvParameters){

}

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  xTaskCreate(Init_Sistema,"INICIALIZAR",configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL);
  xTaskCreate(Mostrar_pantalla, "PANTALLA", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
  //xTaskCreate(Enviar_USB,"USB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
  //xTaskCreate(Cambiar_Modo,"MODO",configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);

  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  vTaskStartScheduler();
  while(1){
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  hi2c1.Init.ClockSpeed = 400000;
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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1500;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */
		//TIMER TRIGGER
  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 8399;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4294967295;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MUX_SEL1_GPIO_Port, MUX_SEL1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MUX_SEL0_Pin|MUX_SEL2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin MUX_SEL1_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|MUX_SEL1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : MUX_SEL0_Pin MUX_SEL2_Pin */
  GPIO_InitStruct.Pin = MUX_SEL0_Pin|MUX_SEL2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  /* USER CODE END Callback 1 */
}

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
