/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.c
  * @brief          : Sources file
  ******************************************************************************
  */

#include "msg/ser_des/serializers/PlatformSetMotorSpeed.h"

#include "main/defs.h"
#include <memory.h>

char* serialize_PlatformSetMotorSpeedReq(PlatformSetMotorSpeedReq* req)
{
    char* data = pvPortMalloc(sizeof(*req));

    memcpy(data, req, sizeof(*req));
    return data;
}

char* serialize_PlatformSetMotorSpeedResp(PlatformSetMotorSpeedResp* resp)
{
    char* data = pvPortMalloc(sizeof(*resp));

    memcpy(data, resp, sizeof(*resp));
    return data;
}
