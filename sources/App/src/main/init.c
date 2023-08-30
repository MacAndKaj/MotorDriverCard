/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : init.c
  * @brief          : Sources for init.h file.
  *                   This file contains definitions of init functions.
  ******************************************************************************
  */

#include "main/init.h"
#include "tasks/rx/interface.h"
#include "tasks/feedback/interface.h"
#include "log/interface.h"

#include <main.h>

void onExtInterrupt(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
        case LeftMotorEncoderB_Pin:
        case RightMotorEncoderB_Pin:
            on_ext_interrupt_feedback(GPIO_Pin);
            break;
        default:
            break;
    }
}

void onPeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // Callbacks with 1kHz frequency
    if (htim->Instance == TIM17)
    {
        periodical_callback_feedback();
    }
}

void onRxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        onReceptionCompleted();
    }
}
