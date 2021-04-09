/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_PLATFORM_CONTROLLER_H
#define MOTORDRIVER_PLATFORM_CONTROLLER_H

#include <stdint.h>

/// Controller struct handle.
typedef struct Controller
{
    uint32_t pwmDuty;
    double error;
} ControllerHandle;

extern ControllerHandle leftControllerHandle;
extern ControllerHandle rightControllerHandle;

/// Sets pwm duty value in ControllerHandle struct.
/// \param handle [struct Controller ptr]
/// \param newPwmDuty [uint32_t] new PWM duty value
void setPwmDuty(ControllerHandle *handle, uint32_t newPwmDuty);

/// Returns pwm duty value from ControllerHandle struct.
/// \param handle [struct Controller ptr]
/// \return [uint32_t] value of pwm duty
uint32_t getPwmDuty(const ControllerHandle *handle);

void setLeftDirection(uint8_t direction);
void setRightDirection(uint8_t direction);

void setLeftPwm(int64_t newPwmDuty);
void setRightPwm(int64_t newPwmDuty);

#endif //MOTORDRIVER_PLATFORM_CONTROLLER_H
