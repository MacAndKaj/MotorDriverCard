/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : <brief>
  ******************************************************************************
  */
#ifndef MDC_MOTORS_INTERFACE_H
#define MDC_MOTORS_INTERFACE_H

#include <cmsis_os2.h>

/// Function to configure MotorsTask
void configureMotors(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle);

/// Runtime function of MotorsTask
void workMotors();

/// Function called from periodical callback with 1kHz freq
void periodicalCallback();

void onExtInterruptMotors(uint16_t GPIO_Pin);

#endif //MDC_MOTORS_INTERFACE_H
