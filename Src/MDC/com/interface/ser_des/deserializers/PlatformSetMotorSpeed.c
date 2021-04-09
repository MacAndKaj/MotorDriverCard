/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.c
  * @brief          : Sources file.
  ******************************************************************************
  */

#include <MDC/com/interface/ser_des/deserializers/PlatformSetMotorSpeed.h>

#include <malloc.h>
#include <memory.h>

PlatformSetMotorSpeedReq* deserialize_PlatformSetMotorSpeedReq(char* data)
{
    PlatformSetMotorSpeedReq* msg = malloc(sizeof(struct PlatformSetMotorSpeedReq));

    memcpy(msg, data, sizeof(struct PlatformSetMotorSpeedReq));
    return msg;
}

PlatformSetMotorSpeedResp* deserialize_PlatformSetMotorSpeedResp(char* data)
{
    PlatformSetMotorSpeedResp* msg = malloc(sizeof(struct PlatformSetMotorSpeedResp));

    memcpy(msg, data, sizeof(struct PlatformSetMotorSpeedResp));
    return msg;
}
