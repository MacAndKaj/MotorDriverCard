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

#include "gpio.h"

/// Function initializing MDC.
/// \return [int]: 0 if not error, 1 - otherwise

//TODO: HalEvents module - proxy module between HAL events and application with subscription mechanism instead of calling functions
void onExtInterrupt(uint16_t GPIO_Pin);
void onPeriodElapsedCallback(TIM_HandleTypeDef *htim);
void onRxCpltCallback(UART_HandleTypeDef *huart);

#endif //MOTORDRIVER_PLATFORM_INIT_H
