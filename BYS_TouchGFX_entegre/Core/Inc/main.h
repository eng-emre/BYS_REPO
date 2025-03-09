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
#include "stm32l4xx_hal.h"

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
#define SPI1_NSS_Pin GPIO_PIN_1
#define SPI1_NSS_GPIO_Port GPIOC
#define DC_Pin GPIO_PIN_2
#define DC_GPIO_Port GPIOC
#define RESET_Pin GPIO_PIN_3
#define RESET_GPIO_Port GPIOC
#define FET_ADC_Pin GPIO_PIN_1
#define FET_ADC_GPIO_Port GPIOA
#define PTC_PULL_Pin GPIO_PIN_2
#define PTC_PULL_GPIO_Port GPIOA
#define SHUT_Pin GPIO_PIN_5
#define SHUT_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOB
#define GPIO_BUTTON_HIGH1_Pin GPIO_PIN_14
#define GPIO_BUTTON_HIGH1_GPIO_Port GPIOB
#define GPIO_BUTTON_HIGH2_Pin GPIO_PIN_15
#define GPIO_BUTTON_HIGH2_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOC
#define ALERT_Pin GPIO_PIN_8
#define ALERT_GPIO_Port GPIOC
#define ALERT_EXTI_IRQn EXTI9_5_IRQn
#define DFETOFF_Pin GPIO_PIN_9
#define DFETOFF_GPIO_Port GPIOC
#define DCHG_Pin GPIO_PIN_8
#define DCHG_GPIO_Port GPIOA
#define DDSG_Pin GPIO_PIN_15
#define DDSG_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_3
#define LED4_GPIO_Port GPIOB
#define CAN1_STB_Pin GPIO_PIN_4
#define CAN1_STB_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
