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

#include "FreeRTOS.h" // for pvPortMalloc

#include <memory.h>

PlatformSetMotorPwmValueReq* deserialize_PlatformSetMotorPwmValueReq(const char* data)
{
    PlatformSetMotorPwmValueReq* msg = (PlatformSetMotorPwmValueReq*)pvPortMalloc(sizeof(struct PlatformSetMotorPwmValueReq));

    memcpy(msg, data, sizeof(struct PlatformSetMotorPwmValueReq));
    return msg;
}
