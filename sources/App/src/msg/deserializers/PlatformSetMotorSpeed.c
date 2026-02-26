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

#include "FreeRTOS.h" // for pvPortMalloc

#include <memory.h>

PlatformSetMotorSpeedReq* deserialize_PlatformSetMotorSpeedReq(const char* data)
{
    PlatformSetMotorSpeedReq* msg = pvPortMalloc(sizeof(struct PlatformSetMotorSpeedReq));

    memcpy(msg, data, sizeof(PlatformSetMotorSpeedReq));
    return msg;
}
