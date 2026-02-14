/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : encoder.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include "modules/feedback/impl/encoder.h"

#include "main/defs.h"
#include "modules/log/interface.h"

#include <stdbool.h>
#include <math.h>

void print_pulses(const struct encoder_data *handle)
{
    LOG_INFO_ARGS("[feedback] Pulses - %d\n", handle->pulses);
}

void set_forward(struct encoder_data *handle)
{
    handle->direction = FORWARD;
}

bool is_forward(const struct encoder_data *handle)
{
    return handle->direction == FORWARD;
}

void set_backward(struct encoder_data *handle)
{
    handle->direction = BACKWARD;
}

void set_pulses(struct encoder_data *handle, int32_t newPulses)
{
    handle->pulses = newPulses;
}

int32_t get_pulses(const struct encoder_data *handle)
{
    return handle->pulses;
}

void set_speed(struct encoder_data *handle, double v)
{
    handle->speed = v;
}

void evaluate_speed(struct encoder_data *handle, double t)
{
    if (fabs(t-0.) < 0.0001) return;

    double pulses_done = get_pulses(handle);
    set_pulses(handle, 0);

    set_speed(handle, (2.*M_PI*pulses_done) / (t*PULSES_PER_ROUND));
}

double get_speed(const struct encoder_data* handle)
{
    return handle->speed;
}

// New approach

void encoder_init_new(struct encoder_data *handle)
{
    set_speed(handle, 0);
    set_pulses(handle, 0);
    set_forward(handle);
    handle->start_encoder();
}

void encoder_update(struct encoder_data *handle, double t)
{
    handle->pulses = handle->get_encoder_pulses();
    if (handle->pulses < 0)
    {
        set_backward(handle);
    }
    else
    {
        set_forward(handle);
    }
    evaluate_speed(handle, t);
}
