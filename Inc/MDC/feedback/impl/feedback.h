/**
  ******************************************************************************
  * @file           : motor.h
  * @brief          : Header for main.c file.
  *                   This file contains the motor struct definition.
  ******************************************************************************
  */
#ifndef MDC_FEEDBACK_IMPL_FEEDBACK_H
#define MDC_FEEDBACK_IMPL_FEEDBACK_H

#include <gpio.h>

#include <stdbool.h>
#include <cmsis_os2.h>

struct MotorFeedback;


void configure_feedback_impl(osMessageQueueId_t *speedMeasQueueHandle, osThreadId_t *feedbackThreadIdHandle);
void work_feedback_impl();
void periodical_callback_feedback_impl();
void on_ext_interrupt_feedback_impl(uint16_t GPIO_Pin);

#endif //MDC_FEEDBACK_IMPL_FEEDBACK_H