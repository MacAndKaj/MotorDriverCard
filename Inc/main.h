/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f0xx_hal.h"

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
#define TIM2_PERIOD 10000-1
#define TIM3_PERIOD 10000-1
#define TIM3_PRESCALER 0
#define TIM17_PRESCALER 1000-1
#define TIM17_PERIOD 480-1
#define UserButton_Pin GPIO_PIN_13
#define UserButton_GPIO_Port GPIOC
#define UserButton_EXTI_IRQn EXTI4_15_IRQn
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define MotorWireGreen_Pin GPIO_PIN_6
#define MotorWireGreen_GPIO_Port GPIOA
#define LeftMotorPWM_Pin GPIO_PIN_10
#define LeftMotorPWM_GPIO_Port GPIOB
#define RightMotorEncoderA_Pin GPIO_PIN_6
#define RightMotorEncoderA_GPIO_Port GPIOC
#define LeftMotorIn1_Pin GPIO_PIN_7
#define LeftMotorIn1_GPIO_Port GPIOC
#define RightMotorEncoderB_Pin GPIO_PIN_8
#define RightMotorEncoderB_GPIO_Port GPIOC
#define RightMotorEncoderB_EXTI_IRQn EXTI4_15_IRQn
#define RightMotorIn1_Pin GPIO_PIN_8
#define RightMotorIn1_GPIO_Port GPIOA
#define RightMotorIn2_Pin GPIO_PIN_9
#define RightMotorIn2_GPIO_Port GPIOA
#define LeftMotorEncoderB_Pin GPIO_PIN_10
#define LeftMotorEncoderB_GPIO_Port GPIOC
#define LeftMotorEncoderB_EXTI_IRQn EXTI4_15_IRQn
#define LeftMotorEncoderA_Pin GPIO_PIN_12
#define LeftMotorEncoderA_GPIO_Port GPIOC
#define RightMotorPWM_Pin GPIO_PIN_4
#define RightMotorPWM_GPIO_Port GPIOB
#define LeftMotorIn2_Pin GPIO_PIN_6
#define LeftMotorIn2_GPIO_Port GPIOB
#define SpeedUpdatePin_Pin GPIO_PIN_9
#define SpeedUpdatePin_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
