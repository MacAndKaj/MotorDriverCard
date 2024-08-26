/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <modules/controller/impl/motor_process.h>

#include <modules/controller/interface.h>
#include <main/defs.h>

#include <stdlib.h>

void set_left_direction(struct motor_control_info* u, Dir direction);
void set_right_direction(struct motor_control_info* u, Dir direction);

uint32_t get_pwm_duty(const struct motor_control_info *handle)
{
    return handle->current_values.pwm_duty;
}

void set_pwm_duty(struct motor_control_info *handle, uint32_t new_pwm_duty)
{
    if (new_pwm_duty < handle->stop_threshold)
    {
        new_pwm_duty = 0;
    }

    if (new_pwm_duty > handle->pwm_period)
    {
        new_pwm_duty = handle->pwm_period;
    }
    handle->current_values.pwm_duty = new_pwm_duty;
}

void motor_process_init(struct motor_control_info* left_motor_info, struct motor_control_info* right_motor_info)
{
    set_pwm_duty(left_motor_info, 0);
    set_left_direction(left_motor_info, Forward);

    set_pwm_duty(right_motor_info, 0);
    set_right_direction(right_motor_info, Forward);

    left_motor_info->motor_info_handle->start_pwm(&left_motor_info->current_values.pwm_duty);
    right_motor_info->motor_info_handle->start_pwm(&right_motor_info->current_values.pwm_duty);
}

void motor_process_update_u(struct motor_control_info *ctrl_info, int64_t u, bool leftMotor)
{
    if (u < 0 && ctrl_info->current_values.direction == Forward)
    {
        leftMotor ? set_left_direction(ctrl_info, BACKWARD) : set_right_direction(ctrl_info, BACKWARD);
        ctrl_info->current_values.direction = Backward;
    }
    else if (u > 0 && ctrl_info->current_values.direction == Backward)
    {
        leftMotor ? set_left_direction(ctrl_info, FORWARD) : set_right_direction(ctrl_info, FORWARD);
        ctrl_info->current_values.direction = Forward;
    }
    set_pwm_duty(ctrl_info, llabs(u));
}

void set_left_direction(struct motor_control_info *ctrl_info, Dir direction)
{
    uint32_t pwm_duty_temp = get_pwm_duty(ctrl_info);
    struct motor_pinout *pinout = &ctrl_info->motor_info_handle->pinout;
    set_pwm_duty(ctrl_info, 0);
    if (direction == Forward)
    {
        HAL_GPIO_WritePin(pinout->motorControl1Port, pinout->motorControl1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(pinout->motorControl2Port, pinout->motorControl2Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(pinout->motorControl1Port, pinout->motorControl1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pinout->motorControl2Port, pinout->motorControl2Pin, GPIO_PIN_RESET);
    }
    set_pwm_duty(ctrl_info, pwm_duty_temp);
}

void set_right_direction(struct motor_control_info *ctrl_info, Dir direction)
{
    uint32_t pwm_duty_temp = get_pwm_duty(ctrl_info);
    struct motor_pinout *pinout = &ctrl_info->motor_info_handle->pinout;
    set_pwm_duty(ctrl_info, 0);
    if (direction == Forward)
    {
        HAL_GPIO_WritePin(pinout->motorControl1Port, pinout->motorControl1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pinout->motorControl2Port, pinout->motorControl2Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(pinout->motorControl1Port, pinout->motorControl1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(pinout->motorControl2Port, pinout->motorControl2Pin, GPIO_PIN_SET);
    }
    set_pwm_duty(ctrl_info, pwm_duty_temp);
}
