/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_CONTROLLER_IMPL_MOTORS_H
#define MDC_CONTROLLER_IMPL_MOTORS_H

#include <modules/controller/interface.h>
#include <modules/controller/impl/motor_process.h>

struct controller_internal_data
{
    struct motor_control_info right_motor_control_info;
    struct motor_control_info left_motor_control_info;
    bool disable_pid;
};

void controller_init(struct controller_data *handle);
void controller_work(struct controller_data *handle);

#endif //MDC_CONTROLLER_IMPL_MOTORS_H
