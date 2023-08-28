/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include "tasks/controller/interface.h"

#include "tasks/controller/impl/controller.h"

#include <cmsis_os2.h>

void configure_controller(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle, osMessageQueueId_t* speedValuesQueueHandle)
{
    configure_controller_impl(threadIdHandle, messageQueueHandle, speedValuesQueueHandle);
}

void work_controller()
{
    work_controller_impl();
}
