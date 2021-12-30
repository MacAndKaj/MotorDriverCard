/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/motors/impl/motor_process.h>
#include <MDC/main/defs.h>

#include "gpio.h"

#include <stdlib.h>

typedef enum {
    Forward,
    Backward
} Dir;

struct ControlParameters
{
    uint32_t pwmDuty;
    Dir currentDirection;
};

void setPwmDuty(struct ControlParameters *handle, uint32_t newPwmDuty)
{
    if (newPwmDuty < STOP_THRESHOLD)
    {
        newPwmDuty = 0;
    }

    if (newPwmDuty > PWM_PERIOD)
    {
        newPwmDuty = PWM_PERIOD;
    }
    handle->pwmDuty = newPwmDuty;
}

uint32_t getPwmDuty(const struct ControlParameters *handle)
{
    return handle->pwmDuty;
}

void setLeftDirection(struct OutputConfiguration* u, Dir direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(u->parameters);
    setPwmDuty(u->parameters, 0);
    if (direction == Forward)
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_RESET);
    }
    setPwmDuty(u->parameters, pwm_duty_temp);
}

void setRightDirection(struct OutputConfiguration* u, uint8_t direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(u->parameters);
    setPwmDuty(u->parameters, 0);
    if (direction == Forward)
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_SET);
    }
    setPwmDuty(u->parameters, pwm_duty_temp);
}

void updateU(struct OutputConfiguration* u, int64_t newPwmDuty, bool leftMotor)
{
    if (newPwmDuty < 0 && u->parameters->currentDirection == Forward)
    {
        leftMotor ? setLeftDirection(u, BACKWARD) : setRightDirection(u, FORWARD);
    }
    else if (newPwmDuty > 0 && u->parameters->currentDirection == Backward)
    {
        leftMotor ? setLeftDirection(u, FORWARD) : setRightDirection(u, BACKWARD);
    }
    setPwmDuty(u->parameters, llabs(newPwmDuty));
}