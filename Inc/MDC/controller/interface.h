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
void configure_controller(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle);

/// Runtime function of MotorsTask
void work_controller();

/// Function called from periodical callback with 1kHz freq
void periodical_callback_controller();

void on_ext_interrupt_controller(uint16_t GPIO_Pin);

#endif //MDC_CONTROLLER_INTERFACE_H
