/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : platform_set_motor_speed_req_handler.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <modules/controller/impl/handlers/platform_set_motor_speed_req_handler.h>

#include <stdint.h>

struct
{
    platform_set_motor_speed_req_callback callback;
    struct controller_internal_data *handle;
} platform_set_motor_speed_req_handler;

void platform_set_motor_speed_req_handler_configure(struct controller_internal_data *h,
    platform_set_motor_speed_req_callback cb)
{
    platform_set_motor_speed_req_handler.callback = cb;
    platform_set_motor_speed_req_handler.handle = h;
}

double transformSpeed(int8_t speedInt, uint8_t speedFl)
{
    if (speedInt < 0)
    {
        return speedInt - (speedFl * 0.01);
    }
    return speedInt + (speedFl * 0.01);
}

void platform_set_motor_speed_req_handler_handle(const PlatformSetMotorSpeedReq* msg)
{
    if (platform_set_motor_speed_req_handler.callback == NULL)
    {
        return;
    }

    int8_t lSpeedI = msg->lSpeedI;
    uint8_t lSpeedF = msg->lSpeedF;
    int8_t rSpeedI = msg->rSpeedI;
    uint8_t rSpeedF = msg->rSpeedF;

    platform_set_motor_speed_req_handler.callback(platform_set_motor_speed_req_handler.handle,
        transformSpeed(lSpeedI, lSpeedF), transformSpeed(rSpeedI, rSpeedF));
}
