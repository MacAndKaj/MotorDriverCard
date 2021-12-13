/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : init.c
  * @brief          : Sources for init.h file.
  *                   This file contains definitions of init functions.
  ******************************************************************************
  */

#include <MDC/main/init.h>
#include <MDC/platform/motor_control.h>
#include <MDC/platform/platform.h>
#include <MDC/log/interface.h>
#include <MDC/rx/interface.h>
#include <tim.h>

void initPeripheries()
{
    HAL_StatusTypeDef state;
    state = HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, &leftControllerHandle.pwmDuty, ONE_WORD);
    if (state != HAL_OK)
    {
        Error_Handler();
    }

    state = HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, &rightControllerHandle.pwmDuty, ONE_WORD);
    if (state != HAL_OK)
    {
        Error_Handler();
    }

    state = HAL_TIM_Base_Start_IT(&htim17);
    if (state != HAL_OK)
    {
        Error_Handler();
    }
}

int mainInit()
{
    initPlatform();
    initPeripheries();

    return 0;
}

void onExtInterrupt(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
        case LeftMotorEncoderB_Pin:
            leftMotorEncoderCallback();
            break;
        case RightMotorEncoderB_Pin:
            rightMotorEncoderCallback();
            break;
        case MasterInterrupt_Pin:
            LOG("Interrupt!");
            break;
        default:
            break;
    }
}

// Callbacks with 1kHz frequency
void onPeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM17)
    {
        workPlatformPeriodical();
    }
}

void onRxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        onReceptionCompleted();
    }
}

void onTxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART4)
    {
        onTransmitCompleted();
    }
}
