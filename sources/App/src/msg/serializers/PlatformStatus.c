/**
* Copyright (c) 2026 MacAndKaj. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformStatus.c
  * @brief          : Sources file
  ******************************************************************************
  */

#include "msg/serializers/PlatformStatus.h"

#include "main/defs.h"
#include <memory.h>

void serialize_PlatformStatus(const PlatformStatus* msg, uint8_t *out_buf)
{
    memcpy(out_buf, msg, sizeof(*msg));
}
