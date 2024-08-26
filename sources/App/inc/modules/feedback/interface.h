/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_MODULES_FEEDBACK_INTERFACE_H
#define MDC_MODULES_FEEDBACK_INTERFACE_H

#include <cmsis_os.h>
#include "stm32f3xx_hal.h"

#define FEEDBACK_TIMER_INDEX 0

struct module;

struct encoder_pinout
{
    GPIO_TypeDef* encoderAPort;
    uint16_t encoderAPin;
    GPIO_TypeDef* encoderBPort;
    uint16_t encoderBPin;
};

struct encoder_data
{
    double speed;                       /// Speed of motor in radians per second.
    int32_t pulses;                     /// Actual number of pulses read from encoder.
    int32_t previous_pulses;            /// Actual number of pulses read from encoder.
    uint8_t direction;                  /// Actual currentDirection of motor.
    GPIO_PinState lastPinAEncoderState; /// Last state of encoder A pin
    struct encoder_pinout pinout;        /// Pinout configuration
};

struct feedback_data
{
    osThreadId_t* feedback_thread_handle;
    osMessageQueueId_t* speed_meas_queue_handle;
    struct encoder_data *left_encoder_data;
    struct encoder_data *right_encoder_data;
};

void feedback_module_init(struct module *this_module);
void feedback_module_work(struct module *this_module);
void feedback_timer_callback(struct module *this_module);
void feedback_exti_left_callback(struct module *this_module);
void feedback_exti_right_callback(struct module *this_module);

#endif // MDC_MODULES_FEEDBACK_INTERFACE_H
