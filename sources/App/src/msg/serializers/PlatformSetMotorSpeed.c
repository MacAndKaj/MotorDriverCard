/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.c
  * @brief          : Sources file
  ******************************************************************************
  */

#include "msg/serializers/PlatformSetMotorSpeed.h"

#include "main/defs.h"
#include <memory.h>

void serialize_PlatformSetMotorSpeedResp(const PlatformSetMotorSpeedResp* resp, uint8_t *out_buf)
{
    memcpy(out_buf, resp, sizeof(*resp));
}
