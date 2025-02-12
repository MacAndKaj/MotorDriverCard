/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorPwmValue.c
  * @brief          : Sources file.
  ******************************************************************************
  */

#include "msg/deserializers/PlatformSetMotorPwmValue.h"

#include "main/defs.h"
#include <memory.h>

PlatformSetMotorPwmValueReq* deserialize_PlatformSetMotorPwmValueReq(char* data)
{
    PlatformSetMotorPwmValueReq* msg = (PlatformSetMotorPwmValueReq*)pvPortMalloc(sizeof(struct PlatformSetMotorPwmValueReq));

    memcpy(msg, data, sizeof(struct PlatformSetMotorPwmValueReq));
    return msg;
}

PlatformSetMotorPwmValueResp* deserialize_PlatformSetMotorPwmValueResp(char* data)
{
    PlatformSetMotorPwmValueResp* msg = (PlatformSetMotorPwmValueResp*)pvPortMalloc(sizeof(struct PlatformSetMotorPwmValueResp));

    memcpy(msg, data, sizeof(struct PlatformSetMotorPwmValueResp));
    return msg;
}
