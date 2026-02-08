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

#include <cmsis_os2.h>
#include "stm32f3xx_hal.h"

#define FEEDBACK_TIMER_INDEX 0

struct module;
typedef void (*start_tim_encoder_start_func_t)(void);
typedef int16_t (*get_tim_encoder_count_func_t)(void);

struct encoder_data
{
    double speed;                                       /// Speed of motor in radians per second.
    int32_t pulses;                                     /// Actual number of pulses read from encoder.
    uint8_t direction;                                  /// Actual currentDirection of motor.
    GPIO_PinState lastPinAEncoderState;                 /// Last state of encoder A pin
    start_tim_encoder_start_func_t start_encoder;       /// Function to start encoder counting
    get_tim_encoder_count_func_t get_encoder_pulses;    /// Function to retrieve encoder pulses
};

struct feedback_data
{
    osThreadId_t* feedback_thread_handle;
    struct message_subscription *subs;
    int subs_len;
    struct encoder_data *left_encoder_data;
    struct encoder_data *right_encoder_data;
};

void feedback_module_init(struct module *this_module);
void feedback_timer_callback(struct module *this_module);

#endif // MDC_MODULES_FEEDBACK_INTERFACE_H
