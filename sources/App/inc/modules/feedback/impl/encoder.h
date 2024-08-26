/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : encoder.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_MODULES_FEEDBACK_IMPL_ENCODER_H
#define MDC_MODULES_FEEDBACK_IMPL_ENCODER_H

#include <modules/feedback/interface.h>

void encoder_init(struct encoder_data *handle);

void update_encoder(struct encoder_data* handle);

void evaluate_speed(struct encoder_data *handle, double t);

double get_speed(const struct encoder_data* handle);

int32_t get_pulses(const struct encoder_data *handle);

void print_pulses(const struct encoder_data *handle);

#endif // MDC_MODULES_FEEDBACK_IMPL_ENCODER_H
