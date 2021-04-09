/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/platform/motor_control.h>
#include <MDC/main/defs.h>

#include <gpio.h>

#include <stdlib.h>

ControllerHandle leftControllerHandle;
ControllerHandle rightControllerHandle;

void setPwmDuty(ControllerHandle *handle, uint32_t newPwmDuty)
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

uint32_t getPwmDuty(const ControllerHandle *handle)
{
    return handle->pwmDuty;
}

void setLeftDirection(uint8_t direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(&leftControllerHandle);
    setPwmDuty(&leftControllerHandle, 0);
    if (direction == FORWARD)
    {
        HAL_GPIO_WritePin(LeftMotorIn1_GPIO_Port, LeftMotorIn1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LeftMotorIn2_GPIO_Port, LeftMotorIn2_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LeftMotorIn1_GPIO_Port, LeftMotorIn1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LeftMotorIn2_GPIO_Port, LeftMotorIn2_Pin, GPIO_PIN_RESET);
    }
    setPwmDuty(&leftControllerHandle, pwm_duty_temp);
}

void setRightDirection(uint8_t direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(&rightControllerHandle);
    setPwmDuty(&rightControllerHandle, 0);
    if (direction == FORWARD)
    {
        HAL_GPIO_WritePin(RightMotorIn1_GPIO_Port, RightMotorIn1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RightMotorIn2_GPIO_Port, RightMotorIn2_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(RightMotorIn1_GPIO_Port, RightMotorIn1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RightMotorIn2_GPIO_Port, RightMotorIn2_Pin, GPIO_PIN_SET);
    }
    setPwmDuty(&rightControllerHandle, pwm_duty_temp);
}

void setLeftPwm(int64_t newPwmDuty)
{
    if (newPwmDuty < 0)
    {
        setLeftDirection(BACKWARD);
    }
    else
    {
        setLeftDirection(FORWARD);
    }
    setPwmDuty(&leftControllerHandle, llabs(newPwmDuty));
}


void setRightPwm(int64_t newPwmDuty)
{
    if (newPwmDuty < 0)
    {
        setRightDirection(BACKWARD);
    }
    else
    {
        setRightDirection(FORWARD);
    }
    setPwmDuty(&rightControllerHandle, llabs(newPwmDuty));
}
