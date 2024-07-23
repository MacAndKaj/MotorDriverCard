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

void set_previous_pulses(struct encoder_data *handle, int32_t newPulses)
{
    handle->previous_pulses = newPulses;
}

int32_t get_pulses(const struct encoder_data *handle)
{
    return handle->pulses;
}

int32_t get_previous_pulses(const struct encoder_data *handle)
{
    return handle->previous_pulses;
}

void set_speed(struct encoder_data *handle, double v)
{
    handle->speed = v;
}

void set_pinA_state(struct encoder_data *handle, GPIO_PinState s)
{
    handle->lastPinAEncoderState = s;
}

GPIO_PinState get_last_pinA_state(struct encoder_data const* handle)
{
    return handle->lastPinAEncoderState;
}

void encoder_init(struct encoder_data *handle)
{
    struct encoder_pinout* pinout = &handle->pinout;

    set_speed(handle, 0);
    set_pulses(handle, 0);
    set_forward(handle);
    set_pinA_state(handle, HAL_GPIO_ReadPin(pinout->encoderAPort, pinout->encoderAPin));
}

void update_encoder(struct encoder_data* handle)
{
    struct encoder_pinout* pinout = &handle->pinout;

    GPIO_PinState pin_a_state = HAL_GPIO_ReadPin(pinout->encoderAPort, pinout->encoderAPin);
    GPIO_PinState pin_b_state = HAL_GPIO_ReadPin(pinout->encoderBPort, pinout->encoderBPin);

    int32_t change = 1;
    if (get_last_pinA_state(handle) == pin_a_state)
    {
        if ((pin_a_state == GPIO_PIN_SET && pin_b_state == GPIO_PIN_RESET) ||
            (pin_a_state == GPIO_PIN_RESET && pin_b_state == GPIO_PIN_SET))
        {
            change = -1;
        }
    }
    else
    {
        if ((pin_a_state ==  pin_b_state))
        {
            change = -1;
        }
    }

    set_pulses(handle, get_pulses(handle) + change);

    set_pinA_state(handle, pin_a_state);
}


void evaluate_speed(struct encoder_data *handle, double t)
{
    if (fabs(t-0.) < 0.0001) return;

    double pulses_done = (double)get_pulses(handle);
    set_pulses(handle, 0);

    set_speed(handle, (2.*M_PI*pulses_done) / (t*PULSES_PER_ROUND));
}

double get_speed(const struct encoder_data* handle)
{
    return handle->speed;
}
