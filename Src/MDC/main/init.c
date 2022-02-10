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
#include <MDC/motors/interface.h>
#include <MDC/log/interface.h>
#include <MDC/rx/interface.h>
#include <tim.h>

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
            logInfo("Interrupt!");
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
