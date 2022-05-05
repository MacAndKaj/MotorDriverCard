/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : platform_set_motor_speed_req_handler.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <MDC/motors/impl/handlers/platform_set_motor_speed_req_handler.h>

#include <stdint.h>

struct
{
    double *destLSpeed, *destRSpeed;
} platformSetMotorSpeedReqHandler;

void platform_set_motor_speed_req_handler_configure(double *destLSpeed, double *destRSpeed)
{
    platformSetMotorSpeedReqHandler.destRSpeed = destRSpeed;
    platformSetMotorSpeedReqHandler.destLSpeed = destLSpeed;
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
    *platformSetMotorSpeedReqHandler.destRSpeed = transformSpeed(msg->rSpeedI, msg->rSpeedF);
    *platformSetMotorSpeedReqHandler.destLSpeed = transformSpeed(msg->lSpeedI, msg->lSpeedF);
}
