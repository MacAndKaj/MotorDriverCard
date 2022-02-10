/**
  ******************************************************************************
  * @file           : motor.h
  * @brief          : Header for main.c file.
  *                   This file contains the motor struct definition.
  ******************************************************************************
  */
#ifndef MDC_MOTORS_IMPL_FEEDBACK_H
#define MDC_MOTORS_IMPL_FEEDBACK_H

#include <gpio.h>

struct MotorFeedback;

struct FeedbackConfiguration
{
    GPIO_TypeDef* encoderAPort;
    uint16_t encoderAPin;
    GPIO_TypeDef* encoderBPort;
    uint16_t encoderBPin;
    struct MotorFeedback* feedback;
};

// TODO: change to FeedbackHandle configureFeedback(struct FeedbackConfiguration* handle) to avoid passing later configuration for computing purposes
void configureFeedback(struct FeedbackConfiguration* handle);
void updateFeedback(struct FeedbackConfiguration* handle, uint8_t leftSide);
void handleFeedback(struct MotorFeedback *handle, double t);

#endif //MDC_MOTORS_IMPL_FEEDBACK_H