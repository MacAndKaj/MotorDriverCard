/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.c
  * @brief          : Sources file
  ******************************************************************************
  */

#include <msg/ser_des/serializers/PlatformSetMotorSpeed.h>

#include <malloc.h>
#include <memory.h>

char* serialize_PlatformSetMotorSpeedReq(PlatformSetMotorSpeedReq* req)
{
    char* data = malloc(sizeof(*req));

    memcpy(data, req, sizeof(*req));
    return data;
}

char* serialize_PlatformSetMotorSpeedResp(PlatformSetMotorSpeedResp* resp)
{
    char* data = malloc(sizeof(*resp));

    memcpy(data, resp, sizeof(*resp));
    return data;
}
