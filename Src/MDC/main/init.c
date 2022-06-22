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
#include <MDC/controller/interface.h>
#include <MDC/rx/interface.h>
#include <tim.h>

void onExtInterrupt(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
        case LeftMotorEncoderB_Pin:
        case RightMotorEncoderB_Pin:
            on_ext_interrupt_controller(GPIO_Pin);
            break;
        case MasterInterrupt_Pin:
        default:
            break;
    }
}

// Callbacks with 1kHz frequency
void onPeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM17)
    {
        periodical_callback_controller();
    }
}

void onRxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        onReceptionCompleted();
    }
}
