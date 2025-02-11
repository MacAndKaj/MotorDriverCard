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
#define TIM3_PRESCALER 0
#define TIM2_PERIOD (10000-1)
#define TIM16_PERIOD (8000-1)
#define TIM3_PERIOD (10000 - 1)
#define TIM17_PRESCALER (16-1)
#define TIM2_PRESCALER 0
#define TIM17_PERIOD (50000-1)
#define TIM16_PRESCALER (2000-1)
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define LeftMotorPWM_Pin GPIO_PIN_10
#define LeftMotorPWM_GPIO_Port GPIOB
#define SYSCOM_SPI_NSS_Pin GPIO_PIN_12
#define SYSCOM_SPI_NSS_GPIO_Port GPIOB
#define SYSCOM_SPI_SCK_Pin GPIO_PIN_13
#define SYSCOM_SPI_SCK_GPIO_Port GPIOB
#define SYSCOM_SPI_MISO_Pin GPIO_PIN_14
#define SYSCOM_SPI_MISO_GPIO_Port GPIOB
#define SYSCOM_SPI_MOSI_Pin GPIO_PIN_15
#define SYSCOM_SPI_MOSI_GPIO_Port GPIOB
#define LeftMotorIn1_Pin GPIO_PIN_7
#define LeftMotorIn1_GPIO_Port GPIOC
#define RightMotorIn1_Pin GPIO_PIN_8
#define RightMotorIn1_GPIO_Port GPIOA
#define RightMotorIn2_Pin GPIO_PIN_9
#define RightMotorIn2_GPIO_Port GPIOA
#define RightMotorPWM_Pin GPIO_PIN_4
#define RightMotorPWM_GPIO_Port GPIOB
#define LeftMotorIn2_Pin GPIO_PIN_6
#define LeftMotorIn2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

// GPIO instances
// deprecated #define LEFT_MOTOR_ENCODER_PIN_B  0x1
// deprecated #define RIGHT_MOTOR_ENODER_PIN_B  0x2
// SPI instances
#define SPI_INSTANCE_2            2
// TIM instances
#define TIM_INSTANCE_2            2
#define TIM_INSTANCE_3            3
#define TIM_INSTANCE_16           16
#define TIM_INSTANCE_17           17

// GPIO events
#define EXTI_EVENT_IT             0x01
// TIM events
#define TIM_EVENT_IT              0x11
// SPI events
#define SPI_EVENT_TX_CPLT         0x21
#define SPI_EVENT_RX_CPLT         0x22
#define SPI_EVENT_TX_RX_CPLT      0x23
#define SPI_EVENT_TX_HALF_CPLT    0x24
#define SPI_EVENT_RX_HALF_CPLT    0x25
#define SPI_EVENT_TX_RX_HALF_CPLT 0x26

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
