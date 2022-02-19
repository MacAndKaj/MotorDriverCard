/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_MOTORS_IMPL_MOTORS_H
#define MDC_MOTORS_IMPL_MOTORS_H

void configureMotorsImpl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle);
void workMotorsImpl();
void periodicalCallbackImpl();
void onExtInterruptMotorsImpl(uint16_t GPIO_Pin);


#endif //MDC_MOTORS_IMPL_MOTORS_H
