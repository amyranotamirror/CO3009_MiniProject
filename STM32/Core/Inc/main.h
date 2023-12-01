/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#include <stdint.h>
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOA
#define PEDESTRIAN0_RED_Pin GPIO_PIN_0
#define PEDESTRIAN0_RED_GPIO_Port GPIOB
#define PEDESTRIAN0_GREEN_Pin GPIO_PIN_1
#define PEDESTRIAN0_GREEN_GPIO_Port GPIOB
#define TRAFFIC1_RED_Pin GPIO_PIN_12
#define TRAFFIC1_RED_GPIO_Port GPIOB
#define TRAFFIC1_YELLOW_Pin GPIO_PIN_13
#define TRAFFIC1_YELLOW_GPIO_Port GPIOB
#define TRAFFIC1_GREEN_Pin GPIO_PIN_14
#define TRAFFIC1_GREEN_GPIO_Port GPIOB
#define BUTTON0_Pin GPIO_PIN_8
#define BUTTON0_GPIO_Port GPIOA
#define BUTTON1_Pin GPIO_PIN_9
#define BUTTON1_GPIO_Port GPIOA
#define BUTTON2_Pin GPIO_PIN_10
#define BUTTON2_GPIO_Port GPIOA
#define BUTTON3_Pin GPIO_PIN_11
#define BUTTON3_GPIO_Port GPIOA
#define TRAFFIC0_RED_Pin GPIO_PIN_4
#define TRAFFIC0_RED_GPIO_Port GPIOB
#define TRAFFIC0_YELLOW_Pin GPIO_PIN_5
#define TRAFFIC0_YELLOW_GPIO_Port GPIOB
#define TRAFFIC0_GREEN_Pin GPIO_PIN_6
#define TRAFFIC0_GREEN_GPIO_Port GPIOB
#define PEDESTRIAN1_RED_Pin GPIO_PIN_8
#define PEDESTRIAN1_RED_GPIO_Port GPIOB
#define PEDESTRIAN1_GREEN_Pin GPIO_PIN_9
#define PEDESTRIAN1_GREEN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define TIMER_TICK 10
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
