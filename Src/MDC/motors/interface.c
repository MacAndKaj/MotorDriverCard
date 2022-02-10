/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <MDC/motors/interface.h>

#include <MDC/motors/impl/motors.h>

#include <cmsis_os2.h>

void configureMotors(osMessageQueueId_t* receivedMessageQueueHandle)
{
    configureMotorsImpl();
}

void workMotors()
{
    workMotorsImpl();
}

void periodicalCallback()
{
    periodicalCallbackImpl();
}

void onExtInterruptMotors(uint16_t GPIO_Pin)
{
    onExtInterruptMotorsImpl(GPIO_Pin);
}
