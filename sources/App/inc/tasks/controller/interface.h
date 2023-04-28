/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : <brief>
  ******************************************************************************
  */
#ifndef MDC_CONTROLLER_INTERFACE_H
#define MDC_CONTROLLER_INTERFACE_H

#include <cmsis_os2.h>

/// Function to configure MotorsTask
void configure_controller(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle, osMessageQueueId_t* speedValuesQueueHandle);

/// Runtime function of MotorsTask
void work_controller();

#endif //MDC_CONTROLLER_INTERFACE_H
