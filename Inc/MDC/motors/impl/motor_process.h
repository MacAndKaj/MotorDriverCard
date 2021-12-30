/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_MOTORS_IMPL_MOTOR_PROVESS_H
#define MDC_MOTORS_IMPL_MOTOR_PROVESS_H

#include <stdint.h>

#include <stm32f072xb.h>
#include <stdbool.h>

struct ControlParameters;

struct OutputConfiguration
{
    uint32_t pwmPeriod;
    uint32_t stopThreshold;
    GPIO_TypeDef* motorControl1Port;
    uint16_t motorControl1Pin;
    GPIO_TypeDef* motorControl2Port;
    uint16_t motorControl2Pin;
    struct ControlParameters* parameters;
};

void updateU(struct OutputConfiguration* u, int64_t newPwmDuty, bool leftMotor);

#endif //MDC_MOTORS_IMPL_MOTOR_PROVESS_H
