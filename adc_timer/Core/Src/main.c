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
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define ATEN_03		0	//A0
#define ATEN_05		1	//A1
#define AMP_1		2	//A2
#define AMP_3		3	//A3
#define AMP_5		4	//A4
#define AMP_10		5	//A5
#define AMP_31		6	//A6
#define AMP_50		7	//A7

#define MAX_SIZE			512

#define	ENC_F1		1
#define	ENC_F2		2
#define	ENC_F3		3
#define	ENC_F4		4
#define	ENC_F5		5
#define	ENC_F6		6
#define	ENC_F7		7

#define FS_1		42857
#define FS_2		10769
#define FS_3		2675
#define FS_4		667
#define FS_5		168
#define FS_6		60
#define FS_7		30

#define AMPLITUD	0
#define BASE_TEMP	1
#define TRIGGER		2
#define DEBOUNCE	200
#define VALOR_ACT	((int)-1)

  /*
  htim3.Init.Period = 60;	fs = 700kHz  fmin = 7,142KHz	fmax = 28,57kHz
  htim3.Init.Period = 168;	fs = 250kHz  fmin = 2560Hz fmax = 10,24kHz
  htim3.Init.Period = 667;  fs = 63KHz   fmin = 640Hz fmax = 2560Hz

  htim3.Init.Period = 2675; fs=15,7KHz fmin = 160Hz fmax = 640Hz
  htim3.Init.Period = 10769; fs=3,9KHz fmin = 40Hz fmax = 160Hz
  htim3.Init.Period = 42857; fs=980Hz fmin = 10Hz fmax = 40Hz
  */
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
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

/* USER CODE BEGIN PV */
uint32_t buffer_usb[MAX_SIZE];
uint32_t buffer_adc[MAX_SIZE];
uint32_t buffer_display[MAX_SIZE/2];

QueueHandle_t qEncoder;
QueueHandle_t qTrigger;
QueueHandle_t qRMS;
QueueHandle_t qDelay;

//const float parametro1;
//const float parametro2;

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
static void MX_TIM4_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
/*
void int_to_char(uint32_t num, char texto[]){

	uint32_t buffer = num;
	int contador = 0;
	int pos = 0;
	int digito = 0;

	while(buffer > 0){
		buffer /= 10;
		contador++;
	}

	texto[contador] = '\0';
	buffer = num;

	pos = contador - 1;

	while(pos >= 0){

		digito = buffer % 10;
		buffer /= 10;
		texto[pos] = digito + '0';
		pos--;
	}
}
*/
void rms_to_char(float rms, char rms_char[]){

	int entero = (int)rms;							// 1,648 --> entero = 1
	int decimal = (int)((rms - entero)*1000);		// 1,648 --> decimal = 648

	int decimal_3 = decimal % 10;					// 1,648 --> dec3 = 8;
	int decimal_2 = (decimal/10) % 10;				// 1,648 --> dec2 = 4;
	int decimal_1 = decimal / 100;					// 1,648 --> dec1 = 6:

	if(entero == 0) {

		rms_char[0] = '.';
		rms_char[1] = decimal_1 + '0';

		if(decimal_3 >= 5 && decimal_2 < 9) rms_char[2] = (decimal_2 + 1) + '0';

		else if(decimal_3 >= 5 && decimal_3 == 9){
			rms_char[1]++;
			rms_char[2] = '0';
		}

		else if(decimal_3 < 5 && decimal_3 >= 0) rms_char[2] = decimal_2 + '0';

	}
	else if(entero > 0){

		rms_char[0] = entero + '0';
		rms_char[1] = '.';

		if(decimal_2 >= 5 && decimal_1 < 9) rms_char[2] = (decimal_1+1) + '0';

		else if(decimal_2 >= 5 && decimal_1 == 9){
			rms_char[0]++;
			rms_char[2] = '0';
		}

		else if(decimal_2 < 5) rms_char[2] = decimal_1 + '0';
	}
	rms_char[3] = 'V';
	rms_char[4] = '\0';
}

void freq_to_char(uint32_t Frecuencia, uint8_t *pData){

	Frecuencia = (uint32_t)(1.024 * ((float) Frecuencia) -2.1196);

	// Frecuencias entre 10K y 100K
	if(Frecuencia >= 10000 && Frecuencia < 100000){

		pData[0] = (uint8_t)((Frecuencia/10000) + '0'); 			// 15300/10000  = 1
		Frecuencia %=10000;                             			// 15300 % 10000 = 5300
		pData[1] = (uint8_t)((Frecuencia/1000) + '0');  			// 5300 / 1000 = 5
		Frecuencia %= 1000;                             			// 5300 % 1000 = 300
		pData[2] = ',';
		pData[3] = (uint8_t)((Frecuencia/100) + '0');   			// 300 / 100 = 3
		pData[4] = 'K';
		pData[5] = 'H';
	}

	// Frecuencias entre 0 y 9999
	else if(Frecuencia > 0){

		if(Frecuencia <1000) pData[0] = ' ';
		else pData[0] = (uint8_t)((Frecuencia/1000) + '0'); 		// 9375 / 1000 = 9

		Frecuencia %= 1000;                          				// 9375 % 1000 = 375
		if(Frecuencia < 100 && pData[0] == ' ') pData[1] = ' ';
		else pData[1] = (uint8_t)((Frecuencia/100) + '0');  		// 375 / 100 = 3

		Frecuencia %= 100;                             				// 375 % 100 = 75
		if(Frecuencia < 10 && pData[1] == ' ') pData[2] = ' ';
		else pData[2] = (uint8_t)((Frecuencia/10) + '0');   		// 75 / 10 = 7

		Frecuencia %= 10;                              				// 75 % 10 = 5
		pData[3] = (uint8_t)(Frecuencia + '0');        				// 5

		pData[4] = 'H';
		pData[5] = 'z';
	}

	pData[6] = '\0';
}

float map(float x, float in_min, float in_max, float out_min, float out_max){

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void display_plot_escala(int contador){

	switch(contador){

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

	ssd1306_VLine(26, 9, 55, White);   // left vertical line
	ssd1306_VLine(127, 9, 3, White);   // right vertical line up
	ssd1306_VLine(127, 60, 3, White);  // right vertical line bottom

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

	//ssd1306_SetCursor(14, 0);
	//ssd1306_WriteString("XX.XKH rmsX.XV XXuS", Font_6x8, White);

}

void display_plot_trigger(int trigger){

	int trigger_actual = 0;

	trigger_actual = map(trigger, 0, 4095, 63, 9);

	// dibujo el triangulo
	ssd1306_VLine(127, trigger_actual-2, 4, White);
	ssd1306_VLine(126, trigger_actual-1, 2, White);
	ssd1306_DrawPixel(125, trigger_actual, White);
}

void display_plot_signal(void){

	int y3 = 0, y4 = 0;
	int x3 = 0, x4 = 0;
	int trigger_point = 1;
	int nivel_trigger = 0;

	if(uxQueueMessagesWaiting(qTrigger) == 1)
		xQueueReceive(qTrigger, &nivel_trigger, portMAX_DELAY);

	for(int i=0; i<=98; i++){

		if((buffer_display[i] > nivel_trigger ) && (buffer_display[i+1]) < nivel_trigger){
			trigger_point = i;
			break;
		}
	}

	for(int k=0; k<=98; k++){

		x3 = k + trigger_point;
		x4 = x3 + 1;

		y3 = map(buffer_display[x3], 0, 4095, 63, 9);
		y4 = map(buffer_display[x4], 0, 4095, 63, 9);

		ssd1306_Line(k + 27, y3, k + 28, y4, White);
	 }
	display_plot_trigger(nivel_trigger);
	HAL_ADC_Start_DMA(&hadc1, buffer_adc, MAX_SIZE);
}

void display_plot_rms(void){

	char rms_valor[5];
	static float valor = 0.0;

	if(uxQueueMessagesWaiting(qRMS) == 1)
		xQueueReceive(qRMS, &valor, portMAX_DELAY);

	rms_to_char(valor, rms_valor);
	ssd1306_SetCursor(56, 0);
	ssd1306_WriteString("rms",Font_6x8,White);
	ssd1306_SetCursor(74, 0);
	ssd1306_WriteString(rms_valor,Font_6x8,White);
}

void display_plot_tiempo(int base_temp){

	ssd1306_SetCursor(104,0);

	switch(base_temp){

		case ENC_F1: ssd1306_WriteString(" 25m", Font_6x8, White);
		break;

		case ENC_F2: ssd1306_WriteString("6.3m", Font_6x8, White);
		break;

		case ENC_F3: ssd1306_WriteString("1,6m", Font_6x8, White);
		break;

		case ENC_F4: ssd1306_WriteString("389u", Font_6x8, White);
		break;

		case ENC_F5: ssd1306_WriteString(" 98u", Font_6x8, White);
		break;

		case ENC_F6: ssd1306_WriteString(" 35u", Font_6x8, White);
		break;

		case ENC_F7: ssd1306_WriteString(" 17u", Font_6x8, White);
		break;
	}
}

void display_plot_freq(int freq){

	uint8_t str_freq[7] = {'\0'};
	static int frecuencia = 0;

	// La variable se actualiza en el callback
	// En el main le voy a mandar -1 para que no actualice el valor
	// Pero que el display siga mostrando un valor
	if(freq >= 0) frecuencia = freq;

	ssd1306_SetCursor(14, 0);
	freq_to_char(frecuencia, str_freq);
	ssd1306_WriteString((char *)str_freq,Font_6x8, White);
}

void display_plot_encoder(int encoder_mode){

	ssd1306_SetCursor(0, 0);

	switch(encoder_mode){

		case AMPLITUD: ssd1306_WriteString("A", Font_6x8, White); break;

		case BASE_TEMP: ssd1306_WriteString("t", Font_6x8, White);break;

		case TRIGGER: ssd1306_WriteString("T", Font_6x8, White); break;
	}
}

void mux_select_escala(int contador){

	switch(contador){

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

void ADC_sampling(int periodo){

	int delay = 20;
	if(periodo == FS_1)
	{
		delay = 270;
		xQueueSend(qDelay, &delay, portMAX_DELAY);
	}
	else if(periodo == FS_2)
	{
		delay = 70;
		xQueueSend(qDelay, &delay, portMAX_DELAY);
	}
	else
		xQueueSend(qDelay, &delay, portMAX_DELAY);

	HAL_TIM_Base_Stop(&htim3);

	htim3.Init.Period = periodo;
	HAL_TIM_Base_Init(&htim3);

	HAL_TIM_Base_Start(&htim3);
}

void adc_select_frecuencia(int contador){

	switch(contador){

		case ENC_F1: ADC_sampling(FS_1); break;

		case ENC_F2: ADC_sampling(FS_2); break;

		case ENC_F3: ADC_sampling(FS_3); break;

		case ENC_F4: ADC_sampling(FS_4); break;

		case ENC_F5: ADC_sampling(FS_5); break;

		case ENC_F6: ADC_sampling(FS_6); break;

		case ENC_F7: ADC_sampling(FS_7); break;
	}
}

void encoder_pos(void){

	static int16_t counter_act = 0;
	static int16_t counter_viejo = 0;

	static int counter_amp = AMP_1;
	static int counter_temp = ENC_F6;
	static int seleccion = 0;
	static int trigger_level = 2090;

	counter_act = TIM4->CNT/2;

	if(uxQueueMessagesWaiting(qEncoder) == 1)
		xQueueReceive(qEncoder, &seleccion, portMAX_DELAY);

	switch(seleccion){

		case AMPLITUD: //AMPLITUD

			if(counter_act > counter_viejo && counter_amp < 7)
				counter_amp++;

			else if(counter_act > counter_viejo && counter_amp == 7)
				counter_amp = AMP_1;

			else if(counter_act < counter_viejo && counter_amp > 0)
				counter_amp--;

			mux_select_escala(counter_amp);

		break;

		case BASE_TEMP: //BASE TEMPORAL

			if(counter_act > counter_viejo && counter_temp < 7){
				counter_temp++;
				adc_select_frecuencia(counter_temp);
			}

			else if(counter_act < counter_viejo && counter_temp > 1){
				counter_temp--;
				adc_select_frecuencia(counter_temp);
			}

			break;

		case TRIGGER: // NIVEL TRIGGER

			if(counter_act > counter_viejo && trigger_level < 3990)
				trigger_level+=100;

			else if(counter_act > counter_viejo && trigger_level == 3990)
				trigger_level = 90;

			if(counter_act < counter_viejo && trigger_level >= 190)
				trigger_level-=100;
			else if(counter_act < counter_viejo && trigger_level == 90)
				trigger_level = 3990;
		break;

		default: break;
	}
	xQueueSend(qTrigger,&trigger_level,portMAX_DELAY);
	//display_plot_trigger(trigger_level);
	display_plot_escala(counter_amp);
	display_plot_tiempo(counter_temp);
	display_plot_encoder(seleccion);

	counter_viejo = counter_act;
}
/* ------------------------ Tareas Free RTOS ------------------------ */

void Init_Sistema(void *pvParameters){

	ssd1306_Init();
	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1);
	HAL_ADC_Start_DMA(&hadc1, buffer_adc, MAX_SIZE);
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_ALL);
	mux_select_escala(AMP_1);

	vTaskDelete(NULL);
}

void Mostrar_pantalla(void *pvParameters){

	int delay_display = 0;
	while(1){

		if(uxQueueMessagesWaiting(qDelay) == 1)
			xQueueReceive(qDelay, &delay_display, portMAX_DELAY);

		display_plot_grilla();
		display_plot_signal();
		display_plot_freq(VALOR_ACT);
		display_plot_rms();
		encoder_pos();
		ssd1306_UpdateScreen();
		vTaskDelay(delay_display/portTICK_RATE_MS);
	}
}

void Cambiar_Modo(void *pvParameters){

}

void Enviar_USB(void *pvParameters){

}

/* --------------------------- Callbacks --------------------------- */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	static uint32_t previousMillis = 0;
	uint32_t currentMillis = 0;
	static int encoder = 0;

	currentMillis = HAL_GetTick();
	if (GPIO_Pin == GPIO_PIN_9 && (currentMillis - previousMillis > DEBOUNCE))
	{
		previousMillis = currentMillis;
		encoder++;
		encoder%=3;

		xQueueSendFromISR(qEncoder,&encoder,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken )
	}
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc){

	for(int i = 0; i<MAX_SIZE/2; i++){
		buffer_display[i] = buffer_adc[i];
		buffer_usb[i] = buffer_adc[i];
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	float mean = 0.0;
	float suma = 0.0;
	float valorMax = 0.0;
	float RMS = 0.0;

	for(int i = 0; i<MAX_SIZE/2; i++){

		buffer_display[i] = buffer_adc[i+256];
		buffer_usb[i + 256] = buffer_adc[i +256];
		mean += buffer_adc[i];
	}

	mean = 2*mean/MAX_SIZE;

	for(int i=0; i<MAX_SIZE; i++){
		suma = (float)(buffer_adc[i]) - mean;
		suma = suma*(3.3/4095);
		valorMax = suma*suma+valorMax;
	}
	RMS = sqrt((valorMax / MAX_SIZE));
	valorMax = 0;

	xQueueSendFromISR(qRMS,&RMS,&xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){

	static uint32_t tiempo_init = 0;
	static uint32_t tiempo_act = 0;
	static uint32_t freq = 0;

	if(!freq) tiempo_init = TIM5->CNT;

	tiempo_act = TIM5->CNT;

	if((tiempo_act - tiempo_init) < 2000) freq++;

	else{
		display_plot_freq(freq);
		freq = 0;
	}
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  qEncoder = xQueueCreate(1,sizeof(int));
  qTrigger = xQueueCreate(1,sizeof(int));
  qRMS = xQueueCreate(1,sizeof(float));
  qDelay = xQueueCreate(1,sizeof(int));
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */


  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  xTaskCreate(Init_Sistema,"INICIALIZAR",configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL);
  xTaskCreate(Mostrar_pantalla, "PANTALLA", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);

  //xTaskCreate(Enviar_USB,"USB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
  //xTaskCreate(Cambiar_Modo,"MODO",configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);

  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */


  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 // Init_Sistema(NULL);
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
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
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
  htim2.Init.Prescaler = 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 735;
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
  /*
  htim3.Init.Period = 60;	fs = 700kHz  fmin = 7,142KHz	fmax = 28,57kHz
  htim3.Init.Period = 168;	fs = 250kHz  fmin = 2560Hz fmax = 10,24kHz
  htim3.Init.Period = 667;  fs = 63KHz   fmin = 640Hz fmax = 2560Hz

  htim3.Init.Period = 2675; fs=15,7KHz fmin = 160Hz fmax = 640Hz
  htim3.Init.Period = 10769; fs=3,9KHz fmin = 40Hz fmax = 160Hz
  htim3.Init.Period = 42857; fs=980Hz fmin = 10Hz fmax = 40Hz
  */
  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 60;
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
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 10;
  sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 10;
  if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

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
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 41999;
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
  if (HAL_TIM_IC_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim5, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
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

  /*Configure GPIO pin : ENC_SW_Pin */
  GPIO_InitStruct.Pin = ENC_SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ENC_SW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MUX_SEL0_Pin MUX_SEL2_Pin */
  GPIO_InitStruct.Pin = MUX_SEL0_Pin|MUX_SEL2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
