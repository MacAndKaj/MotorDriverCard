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
#include "stm32f3xx_hal.h"

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
#define TIM2_PRESCALER 0
#define TIM2_PERIOD (10000-1)
#define TIM3_PRESCALER 0
#define TIM3_PERIOD (10000 - 1)
#define TIM17_PRESCALER 0
#define TIM17_PERIOD (8000-1)
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define SpeedUpdatePin_Pin GPIO_PIN_7
#define SpeedUpdatePin_GPIO_Port GPIOA
#define LeftMotorPWM_Pin GPIO_PIN_10
#define LeftMotorPWM_GPIO_Port GPIOB
#define MasterInterrupt_Pin GPIO_PIN_13
#define MasterInterrupt_GPIO_Port GPIOB
#define MasterInterrupt_EXTI_IRQn EXTI15_10_IRQn
#define RightMotorEncoderA_Pin GPIO_PIN_6
#define RightMotorEncoderA_GPIO_Port GPIOC
#define LeftMotorIn1_Pin GPIO_PIN_7
#define LeftMotorIn1_GPIO_Port GPIOC
#define RightMotorEncoderB_Pin GPIO_PIN_8
#define RightMotorEncoderB_GPIO_Port GPIOC
#define RightMotorEncoderB_EXTI_IRQn EXTI9_5_IRQn
#define RightMotorIn1_Pin GPIO_PIN_8
#define RightMotorIn1_GPIO_Port GPIOA
#define RightMotorIn2_Pin GPIO_PIN_9
#define RightMotorIn2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define LeftMotorEncoderB_Pin GPIO_PIN_10
#define LeftMotorEncoderB_GPIO_Port GPIOC
#define LeftMotorEncoderB_EXTI_IRQn EXTI15_10_IRQn
#define LeftMotorEncoderA_Pin GPIO_PIN_12
#define LeftMotorEncoderA_GPIO_Port GPIOC
#define RightMotorPWM_Pin GPIO_PIN_4
#define RightMotorPWM_GPIO_Port GPIOB
#define LeftMotorIn2_Pin GPIO_PIN_6
#define LeftMotorIn2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
