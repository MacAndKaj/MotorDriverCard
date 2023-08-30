/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : platform_set_motor_speed_req_handler.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include "tasks/controller/impl/handlers/platform_set_motor_speed_req_handler.h"

#include <stdint.h>
#include <stddef.h>

#include <FreeRTOS.h>

struct
{
    void (*callback)(double rs, double ls); 
} platformSetMotorSpeedReqHandler;

void platform_set_motor_speed_req_handler_configure(void (*cb)(double, double))
{
    platformSetMotorSpeedReqHandler.callback = cb;
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
    if (platformSetMotorSpeedReqHandler.callback == NULL)
    {
        return;
    }

    int8_t lSpeedI = msg->lSpeedI;
    uint8_t lSpeedF = msg->lSpeedF;
    int8_t rSpeedI = msg->rSpeedI;
    uint8_t rSpeedF = msg->rSpeedF;

    platformSetMotorSpeedReqHandler.callback(transformSpeed(lSpeedI, lSpeedF), transformSpeed(rSpeedI, rSpeedF));
}
