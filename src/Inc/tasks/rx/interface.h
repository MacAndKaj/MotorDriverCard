/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_RX_INTERFACE_H
#define MDC_RX_INTERFACE_H

#include <cmsis_os2.h>

/// Function to configure RxTask
void configureRx(osThreadId_t *threadIdHandle, osMessageQueueId_t *messageQueueHandle);

/// Callback when new data was received and should be dispatched
void onReceptionCompleted();

/// Runtime function of RxTask
void workRx();

#endif //MDC_RX_INTERFACE_H
