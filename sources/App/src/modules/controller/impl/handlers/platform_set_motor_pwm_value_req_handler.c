/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : platform_set_motor_pwm_value_req_handler.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <modules/controller/impl/handlers/platform_set_motor_pwm_value_req_handler.h>

struct
{
    platform_set_motor_pwm_value_req_callback callback;
    struct controller_internal_data *handle;
} platform_set_motor_pwm_value_req_handler;

void platform_set_motor_pwm_value_req_handler_configure(struct controller_internal_data *h,
                                                        platform_set_motor_pwm_value_req_callback cb)
{
    platform_set_motor_pwm_value_req_handler.callback = cb;
    platform_set_motor_pwm_value_req_handler.handle = h;
}

void platform_set_motor_pwm_value_req_handler_handle(const PlatformSetMotorPwmValueReq *msg)
{
    if (platform_set_motor_pwm_value_req_handler.callback == NULL)
    {
        return;
    }

    int right_pwm = msg->rDirection == 1 ? msg->rPwmValue : -msg->rPwmValue;
    int left_pwm = msg->lDirection == 1 ? msg->lPwmValue : -msg->lPwmValue;


    platform_set_motor_pwm_value_req_handler.callback(platform_set_motor_pwm_value_req_handler.handle,
                                                      left_pwm, right_pwm);
}
