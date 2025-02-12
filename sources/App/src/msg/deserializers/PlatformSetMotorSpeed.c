/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.c
  * @brief          : Sources file.
  ******************************************************************************
  */

#include "msg/deserializers/PlatformSetMotorSpeed.h"

#include "main/defs.h"
#include <memory.h>

PlatformSetMotorSpeedReq* deserialize_PlatformSetMotorSpeedReq(char* data)
{
    PlatformSetMotorSpeedReq* msg = (PlatformSetMotorSpeedReq*)pvPortMalloc(sizeof(struct PlatformSetMotorSpeedReq));

    memcpy(msg, data, sizeof(struct PlatformSetMotorSpeedReq));
    return msg;
}

PlatformSetMotorSpeedResp* deserialize_PlatformSetMotorSpeedResp(char* data)
{
    PlatformSetMotorSpeedResp* msg = (PlatformSetMotorSpeedResp*)pvPortMalloc(sizeof(struct PlatformSetMotorSpeedResp));

    memcpy(msg, data, sizeof(struct PlatformSetMotorSpeedResp));
    return msg;
}
