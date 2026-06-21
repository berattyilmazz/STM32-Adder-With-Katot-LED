/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

/* USER CODE BEGIN PV */

volatile uint8_t analog_variable1 = 0;
volatile uint8_t analog_variable2 = 0;
volatile uint8_t clean_value1 = 0;
volatile uint8_t clean_value2 = 0;
volatile uint8_t button_state = 0;
volatile uint8_t summation = 0;
uint8_t zero = 0;

void Led_1_Numbers(uint8_t number);
void Led_2_Numbers(uint8_t number);
void Led_3_Numbers(uint8_t number);
void Led_4_Numbers(uint8_t number);
uint8_t ADC_Translation_Division(uint8_t variable);
void Print_screen12(uint8_t number);
void Print_screen34(uint8_t number);
uint8_t addition(void);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC2_Init(void);
static void MX_ADC3_Init(void);
/* USER CODE BEGIN PFP */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc->Instance == ADC2) {
		analog_variable1 = HAL_ADC_GetValue(&hadc2);
	} else if (hadc->Instance == ADC3) {
		analog_variable2 = HAL_ADC_GetValue(&hadc3);
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void Led_1_Numbers(uint8_t number);

void Led_2_Numbers(uint8_t number);

void Led_3_Numbers(uint8_t number);

void Led_4_Numbers(uint8_t number);

uint8_t ADC_Translation_Division(uint8_t variable);

void Print_screen12(uint8_t number);

void Print_screen34(uint8_t number);

uint8_t addition(void);

void Reset_state(void);

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

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
	MX_ADC2_Init();
	MX_ADC3_Init();
	/* USER CODE BEGIN 2 */
	HAL_ADC_Start_IT(&hadc2);
	HAL_ADC_Start_IT(&hadc3);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		HAL_ADC_Start_IT(&hadc2);
		HAL_ADC_Start_IT(&hadc3);

		clean_value1 = ADC_Translation_Division(analog_variable1);
		clean_value2 = ADC_Translation_Division(analog_variable2);

		button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

		Reset_state();

		if (button_state == 1)
		{
		    summation = addition();

		    Print_screen12(summation);
		    Print_screen34(0);
		}
		else
		{
		    Print_screen12(clean_value1);
		    Print_screen34(clean_value2);
		}

	}
	/* USER CODE END 3 */
}

uint8_t addition(void) {
	return clean_value1 + clean_value2;
}
void Reset_state(void){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_RESET);
}

void Print_screen12(uint8_t number) {
    uint8_t units = number % 10;
    uint8_t tens = number / 10;
    Led_2_Numbers(tens);
    Led_1_Numbers(units);
}

void Print_screen34(uint8_t number) {
    uint8_t units = number % 10;
    uint8_t tens = number / 10;
    Led_4_Numbers(tens);
    Led_3_Numbers(units);
}

uint8_t ADC_Translation_Division(uint8_t variable) {

    if (variable <= 12) return 0;
    else if (variable <= 24) return 1;
    else if (variable <= 36) return 2;
    else if (variable <= 48) return 3;
    else if (variable <= 60) return 4;
    else if (variable <= 72) return 5;
    else if (variable <= 84) return 6;
    else if (variable <= 96) return 7;
    else if (variable <= 108) return 8;
    else if (variable <= 120) return 9;
    else if (variable <= 132) return 10;
    else if (variable <= 144) return 11;
    else if (variable <= 156) return 12;
    else if (variable <= 168) return 13;
    else if (variable <= 180) return 14;
    else if (variable <= 192) return 15;
    else if (variable <= 204) return 16;
    else if (variable <= 216) return 17;
    else if (variable <= 228) return 18;
    else if (variable <= 240) return 19;
    else return 20;

}

void Led_1_Numbers(uint8_t number) {

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);

	if (number == 0) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

	} else if (number == 1) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

	} else if (number == 2) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

	} else if (number == 3) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

	} else if (number == 4) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

	} else if (number == 5) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

	} else if (number == 6) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

	} else if (number == 7) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

	} else if (number == 8) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

	} else if (number == 9) {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

	}

}

void Led_2_Numbers(uint8_t number) {

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);

	if (number == 0) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

	} else if (number == 1) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

	} else if (number == 2) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	} else if (number == 3) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	} else if (number == 4) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

	} else if (number == 5) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	} else if (number == 6) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

	} else if (number == 7) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

	} else if (number == 8) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

	} else if (number == 9) {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

	}

}

void Led_3_Numbers(uint8_t number) {

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

	if (number == 0) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

	} else if (number == 1) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

	} else if (number == 2) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

	} else if (number == 3) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

	} else if (number == 4) {

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

	} else if (number == 5) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

	} else if (number == 6) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

	} else if (number == 7) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

	} else if (number == 8) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

	} else if (number == 9) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

	}

}

void Led_4_Numbers(uint8_t number) {

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);

	if (number == 0) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);

	} else if (number == 1) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

	} else if (number == 2) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

	} else if (number == 3) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

	} else if (number == 4) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

	} else if (number == 5) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

	} else if (number == 6) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);

	} else if (number == 7) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

	} else if (number == 8) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

	} else if (number == 9) {

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

	}

}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief ADC2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC2_Init(void) {

	/* USER CODE BEGIN ADC2_Init 0 */

	/* USER CODE END ADC2_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC2_Init 1 */

	/* USER CODE END ADC2_Init 1 */

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc2.Instance = ADC2;
	hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc2.Init.Resolution = ADC_RESOLUTION_8B;
	hadc2.Init.ScanConvMode = DISABLE;
	hadc2.Init.ContinuousConvMode = DISABLE;
	hadc2.Init.DiscontinuousConvMode = DISABLE;
	hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc2.Init.NbrOfConversion = 1;
	hadc2.Init.DMAContinuousRequests = DISABLE;
	hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc2) != HAL_OK) {
		Error_Handler();
	}

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_13;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC2_Init 2 */

	/* USER CODE END ADC2_Init 2 */

}

/**
 * @brief ADC3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC3_Init(void) {

	/* USER CODE BEGIN ADC3_Init 0 */

	/* USER CODE END ADC3_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC3_Init 1 */

	/* USER CODE END ADC3_Init 1 */

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc3.Instance = ADC3;
	hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc3.Init.Resolution = ADC_RESOLUTION_8B;
	hadc3.Init.ScanConvMode = DISABLE;
	hadc3.Init.ContinuousConvMode = DISABLE;
	hadc3.Init.DiscontinuousConvMode = DISABLE;
	hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc3.Init.NbrOfConversion = 1;
	hadc3.Init.DMAContinuousRequests = DISABLE;
	hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc3) != HAL_OK) {
		Error_Handler();
	}

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC3_Init 2 */

	/* USER CODE END ADC3_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
	GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_11 | GPIO_PIN_12
					| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE,
			GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
					| GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD,
	GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PA2 PA3 PA4 PA5
	 PA6 PA7 */
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
			| GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PC4 PC5 */
	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB2 PB11
	 PB12 PB13 PB14 PB15 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_11
			| GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PE7 PE8 PE9 PE10
	 PE11 PE12 PE13 PE14 */
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
			| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pins : PD8 PD9 PD10 PD11 */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
