/**
  ******************************************************************************
  * @file           : motor.h
  * @brief          : Header for main.c file.
  *                   This file contains the motor struct definition.
  ******************************************************************************
  */
#ifndef MDC_MODULES_FEEDBACK_IMPL_FEEDBACK_H
#define MDC_MODULES_FEEDBACK_IMPL_FEEDBACK_H

#include <modules/feedback/interface.h>

void feedback_start(struct feedback_data *data);

void feedback_work(struct feedback_data *data);

void feedback_update(struct feedback_data *data);

#endif //MDC_MODULES_FEEDBACK_IMPL_FEEDBACK_H
