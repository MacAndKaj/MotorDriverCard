/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : init.c
  * @brief          : Sources for init.h file.
  *                   This file contains definitions of init funcitons.
  ******************************************************************************
  */

#include <MDC/com/com.h>
#include <MDC/main/boolean.h>
#include <MDC/main/defs.h>
#include <MDC/main/init.h>
#include <MDC/main/log.h>
#include <MDC/platform/motor_control.h>
#include <MDC/platform/motor_info.h>
#include <MDC/platform/pid.h>
#include <MDC/com/interface/message_ids.h>
#include <MDC/platform/platform.h>

#include <tim.h>
#include <stdio.h>

/* CONTEXTS BEGIN */

CommunicationContext communicationContext;

/* CONTEXTS END */


/* DECLARATIONS BEGIN */

/// Function initializing STM32 peripheries used in project.
/// \return [int]: 0 if not error, 1 - otherwise
int initPeripheries();


/* DECLARATIONS END */

int mainInit()
{
    if (initPeripheries() != 0)
    {
        printf("Peripheries initialization failed!\r\n");
        return 1;
    }

    initCom(&communicationContext);

    initPlatform();
    subscribe(&communicationContext, PLATFORM_SET_MOTOR_SPEED_REQ_ID, onMessageReceivedPlatform);

    return 0;
}

int initPeripheries()
{
    HAL_StatusTypeDef state;
    state = HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, &leftControllerHandle.pwmDuty, ONE_WORD);
    if (state != HAL_OK)
    {
        printf("Left Motor PWM start failed\r\n");
        return 1;
    }

    state = HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, &rightControllerHandle.pwmDuty, ONE_WORD);
    if (state != HAL_OK)
    {
        printf("Right Motor PWM start failed\r\n");
        return 1;
    }

    state = HAL_TIM_Base_Start_IT(&htim17);
    if (state != HAL_OK)
    {
        printf("Timer start failed\r\n");
        return 1;
    }

    return 0;
}


void onRun(ModuleName moduleName)
{
    switch (moduleName)
    {
        case Com:
            workCom(&communicationContext);
            break;
        case Platform:
            workPlatform();
            break;
        default:
            printf("Unknown module!\r\n");
    }
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
        case UserButton_Pin:
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
    comReceiveCallback(huart, &communicationContext);
}
