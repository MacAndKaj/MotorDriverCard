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
    configure_motors_impl(threadIdHandle, messageQueueHandle);
}

void work_controller()
{
    work_motors_impl();
}

void periodical_callback_controller()
{
    periodical_callback_controller_impl();
}

void on_ext_interrupt_controller(uint16_t GPIO_Pin)
{
    on_ext_interrupt_controller_impl(GPIO_Pin);
}
