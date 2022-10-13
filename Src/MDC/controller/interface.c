/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <MDC/controller/interface.h>

#include <MDC/controller/impl/controller.h>

#include <cmsis_os2.h>

void configure_controller(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    configure_controller_impl(threadIdHandle, messageQueueHandle);
}

void work_controller()
{
    work_controller_impl();
}
