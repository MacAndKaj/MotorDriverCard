/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_RX_IMPL_RX_H
#define MDC_RX_IMPL_RX_H

#include <cmsis_os2.h>

void configureRxImpl(osThreadId_t *threadIdHandle, osMessageQueueId_t *messageQueueHandle);

void onReceptionCompletedImpl();

void workRxImpl();

#endif //MDC_RX_IMPL_RX_H
