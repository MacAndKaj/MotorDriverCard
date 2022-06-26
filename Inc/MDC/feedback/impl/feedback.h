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

struct MotorFeedback;


void configure_feedback_impl();
void work_feedback_impl();
void periodical_callback_controller_impl();
void on_ext_interrupt_feedback_impl(uint16_t GPIO_Pin);


// TODO: change to FeedbackHandle configureFeedback(struct FeedbackConfiguration* handle) to avoid passing later configuration for computing purposes
void update_feedback(struct FeedbackConfiguration* handle, bool leftSide);
void handle_feedback(struct FeedbackConfiguration *handle, double t);
double get_speed(const struct FeedbackConfiguration* handle);

#endif //MDC_FEEDBACK_IMPL_FEEDBACK_H