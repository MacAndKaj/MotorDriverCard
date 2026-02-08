/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformPollStatus.c
  * @brief          : Sources file
  ******************************************************************************
  */

#include "msg/serializers/PlatformPollStatus.h"

#include "main/defs.h"
#include <memory.h>

void serialize_PlatformPollStatusResp(const PlatformPollStatusResp* resp, uint8_t *out_buf)
{
    memcpy(out_buf, resp, sizeof(*resp));
}
