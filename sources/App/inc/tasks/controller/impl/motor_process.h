/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_CONTROLLER_IMPL_MOTOR_PROCESS_H
#define MDC_CONTROLLER_IMPL_MOTOR_PROCESS_H

#include "tim.h"

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    Forward,
    Backward
} Dir;

struct ControlParameters
{
    uint32_t pwmDuty;
    Dir currentDirection;
};

struct OutputConfiguration
{
    uint32_t pwmPeriod;
    uint32_t stopThreshold;
    GPIO_TypeDef* motorControl1Port;
    uint16_t motorControl1Pin;
    GPIO_TypeDef* motorControl2Port;
    uint16_t motorControl2Pin;
    TIM_HandleTypeDef* timer;
    uint32_t channel;
    struct ControlParameters parameters;
};

void motor_process_configure(struct OutputConfiguration* config1, struct OutputConfiguration* config2);
void motor_process_update_u(struct OutputConfiguration* config, int64_t u, bool leftMotor);

#endif //MDC_CONTROLLER_IMPL_MOTOR_PROCESS_H
