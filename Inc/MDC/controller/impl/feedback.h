/**
  ******************************************************************************
  * @file           : motor.h
  * @brief          : Header for main.c file.
  *                   This file contains the motor struct definition.
  ******************************************************************************
  */
#ifndef MDC_CONTROLLER_IMPL_FEEDBACK_H
#define MDC_CONTROLLER_IMPL_FEEDBACK_H

#include <gpio.h>

#include <stdbool.h>

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
void configure_feedback(struct FeedbackConfiguration* handle);
void update_feedback(struct FeedbackConfiguration* handle, bool leftSide);
void handle_feedback(struct FeedbackConfiguration *handle, double t);
double get_speed(const struct FeedbackConfiguration* handle);

#endif //MDC_CONTROLLER_IMPL_FEEDBACK_H