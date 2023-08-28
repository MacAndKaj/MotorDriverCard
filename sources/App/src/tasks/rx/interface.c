/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface of rx task.
  ******************************************************************************
  */

#include "tasks/rx/impl/rx.h"
#include <stddef.h>
#include <stdbool.h>

bool rxInitialized = false;

void configureRx(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    configureRxImpl(threadIdHandle, messageQueueHandle);
    rxInitialized = true;
}

void onReceptionCompleted()
{
    onReceptionCompletedImpl();
}

void workRx()
{
    if (rxInitialized) workRxImpl();
}