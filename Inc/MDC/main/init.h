/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : hal_config.h
  * @brief          : Header for <source file name> file.
  *                   This file contains general functions for MotorDriver.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_PLATFORM_INIT_H
#define MOTORDRIVER_PLATFORM_INIT_H

#include <gpio.h>

#define ONE_WORD 1

typedef enum ModuleName
{
    Com,
    Platform
} ModuleName;

/// Function initializing MDC.
/// \return [int]: 0 if not error, 1 - otherwise
int mainInit();

/// Main function for tasks.
/// \param moduleName enum ModuleName for specific task
void onRun(ModuleName moduleName);

void onExtInterrupt(uint16_t GPIO_Pin);
void onPeriodElapsedCallback(TIM_HandleTypeDef *htim);
void onRxCpltCallback(UART_HandleTypeDef *huart);

#endif //MOTORDRIVER_PLATFORM_INIT_H
