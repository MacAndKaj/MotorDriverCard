/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_CONTROLLER_IMPL_MOTORS_H
#define MDC_CONTROLLER_IMPL_MOTORS_H

void configure_motors_impl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle);
void work_motors_impl();
void periodical_callback_controller_impl();
void on_ext_interrupt_controller_impl(uint16_t GPIO_Pin);


#endif //MDC_CONTROLLER_IMPL_MOTORS_H
