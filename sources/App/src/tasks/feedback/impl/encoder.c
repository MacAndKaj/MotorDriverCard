/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : encoder.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include "tasks/feedback/impl/encoder.h"

#include "main/defs.h"

#include <math.h>
#include <FreeRTOS.h>

struct EncoderPinout
{
    GPIO_TypeDef* encoderAPort;
    uint16_t encoderAPin;
    GPIO_TypeDef* encoderBPort;
    uint16_t encoderBPin;
};

struct EncoderData
{
    double speed;                       /// Speed of motor in radians per second.
    int32_t pulses;                     /// Actual number of pulses read from encoder.
    uint8_t direction;                  /// Actual currentDirection of motor.
    GPIO_PinState lastPinAEncoderState; /// Last state of encoder A pin
    struct EncoderPinout pinout;        /// Pinout configuration
};

void set_forward(struct EncoderData *handle)
{
    handle->direction = FORWARD;
}

int is_forward(const struct EncoderData *handle)
{
    return handle->direction == FORWARD;
}

void set_backward(struct EncoderData *handle)
{
    handle->direction = BACKWARD;
}

void set_pulses(struct EncoderData *handle, int32_t newPulses)
{
    handle->pulses = newPulses;
}

int32_t get_pulses(const struct EncoderData *handle)
{
    return handle->pulses;
}

void set_speed(struct EncoderData *handle, double v)
{
    handle->speed = v;
}

void set_pinA_state(struct EncoderData *handle, GPIO_PinState s)
{
    handle->lastPinAEncoderState = s;
}

void set_pinout(struct EncoderData *handle, const struct EncoderPinout* p)
{
    handle->pinout = *p;
}

struct EncoderData* create_encoder(GPIO_TypeDef* encoderAPort, uint16_t encoderAPin,
    GPIO_TypeDef* encoderBPort, uint16_t encoderBPin)
{
    struct EncoderData* tmp = pvPortMalloc(sizeof(struct EncoderData));
    set_speed(tmp, 0);
    set_pulses(tmp, 0);
    set_forward(tmp);
    set_pinA_state(tmp, HAL_GPIO_ReadPin(encoderAPort, encoderAPin));
    struct EncoderPinout initPinout = {
        .encoderAPort=encoderAPort,
        .encoderAPin=encoderAPin,
        .encoderBPort=encoderBPort,
        .encoderBPin=encoderBPin
    };
    set_pinout(tmp, &initPinout);
}

void update_encoder(struct EncoderData* handle, bool leftSide)
{
    struct EncoderPinout* pinout = &handle->pinout;

    GPIO_PinState state = HAL_GPIO_ReadPin(pinout->encoderAPort, pinout->encoderAPin);
    GPIO_PinState val = HAL_GPIO_ReadPin(pinout->encoderBPort, pinout->encoderBPin);
    GPIO_PinState val1 = GPIO_PIN_SET, val2 = GPIO_PIN_RESET; //TODO: change name to more meaningful
    if (leftSide)
    {
        val1 = GPIO_PIN_RESET;
        val2 = GPIO_PIN_SET;
    }

    if ((handle->lastPinAEncoderState == GPIO_PIN_RESET) && state == GPIO_PIN_SET)
    {

        if (val == val1 && is_forward(handle))
        {
            set_backward(handle);
        }
        else if (val == val2 && !is_forward(handle))
        {
            set_forward(handle);
        }
    }
    set_pinA_state(handle, state);

    int32_t pulses = get_pulses(handle);
    if (is_forward(handle))
    {
        set_pulses(handle, pulses + 1);
    }
    else
    {
        set_pulses(handle, pulses - 1);
    }
}


void evaluate_speed(struct EncoderData *handle, double t)
{
    if (t == 0.) return;

    double rounds = get_pulses(handle) / PULSES_PER_ROUND;
    set_pulses(handle, 0);

    set_speed(handle, 2.*M_PI*rounds / t);
}

double get_speed(const struct EncoderData* handle)
{
    return handle->speed;
}
