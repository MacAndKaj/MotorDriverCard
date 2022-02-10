/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motor.c
  * @brief          : Sources for motor.h file.
  ******************************************************************************
  */
#include <MDC/motors/impl/feedback.h>

#include <MDC/main/defs.h>

#include <math.h>
#include <malloc.h>

struct MotorFeedback
{
    double speed;                       /// Speed of motor in radians per second.
    int32_t pulses;                     /// Actual number of pulses read from encoder.
    uint8_t direction;                  /// Actual currentDirection of motor.
    GPIO_PinState lastPinAEncoderState; /// Last state of encoder A pin
};
typedef struct MotorFeedback MotorFeedback;


/**
  ******************************************************************************
  *
  * General functions begin
  *
  *******************************************************************************
  */
void setForward(MotorFeedback *handle)
{
    handle->direction = FORWARD;
}

int isForward(const MotorFeedback *handle)
{
    return handle->direction == FORWARD;
}

void setBackward(MotorFeedback *handle)
{
    handle->direction = BACKWARD;
}

void setPulses(MotorFeedback *handle, int32_t newPulses)
{
    handle->pulses = newPulses;
}

int32_t getPulses(const MotorFeedback *handle)
{
    return handle->pulses;
}

void setSpeed(MotorFeedback *handle, double newSpeed)
{
    handle->speed = newSpeed;
}

double getSpeed(const MotorFeedback *handle)
{
    return handle->speed;
}

void handleFeedback(MotorFeedback *handle, double t)
{
    if (t == 0.) return;

    double rounds = getPulses(handle) / PULSES_PER_ROUND;
    setPulses(handle, 0);

    setSpeed(handle, 2.*M_PI*rounds / t);
}

void configureFeedback(struct FeedbackConfiguration* handle)
{
    handle->feedback = malloc(sizeof(MotorFeedback));
    setForward(handle->feedback);
    setPulses(handle->feedback, 0);
    setSpeed(handle->feedback, 0);
    handle->feedback->lastPinAEncoderState = HAL_GPIO_ReadPin(handle->encoderAPort,handle->encoderAPin);
}

void updateFeedback(struct FeedbackConfiguration* handle, uint8_t leftSide)
{
    GPIO_PinState state = HAL_GPIO_ReadPin(handle->encoderAPort, handle->encoderAPin);
    GPIO_PinState val = HAL_GPIO_ReadPin(handle->encoderBPort, handle->encoderBPin);
    GPIO_PinState val1 = GPIO_PIN_SET, val2 = GPIO_PIN_RESET; //TODO: change name to more meaningful
    MotorFeedback* fb = handle->feedback;
    if (leftSide == 1 )
    {
        val1 = GPIO_PIN_RESET;
        val2 = GPIO_PIN_SET;
    }

    if ((fb->lastPinAEncoderState == GPIO_PIN_RESET) && state == GPIO_PIN_SET)
    {

        if (val == val1 && isForward(fb))
        {
            setBackward(fb);
        }
        else if (val == val2 && !isForward(fb))
        {
            setForward(fb);
        }
    }
    fb->lastPinAEncoderState = state;

    int32_t pulses = getPulses(fb);
    if (isForward(fb))
    {
        setPulses(fb, pulses + 1);
    }
    else
    {
        setPulses(fb, pulses - 1);
    }
}
