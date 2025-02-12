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

#include <modules/controller/impl/pid.h>

#include <stm32f3xx_hal.h>

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    Forward,
    Backward
} Dir;

struct control_values
{
    uint32_t pwm_duty;
    Dir direction;
    double ref_speed;
    double current_speed;
};

struct motor_control_info
{
    uint32_t pwm_period;
    uint32_t stop_threshold;
    struct control_values current_values;
    struct pid pid_data;
    struct motor_info *motor_info_handle;
};

void motor_process_init(struct motor_control_info* left_motor_info, struct motor_control_info* right_motor_info);
void motor_process_update_u(struct motor_control_info *ctrl_info, int64_t u, bool leftMotor);
uint32_t get_pwm_duty(const struct motor_control_info *handle);

#endif //MDC_CONTROLLER_IMPL_MOTOR_PROCESS_H
