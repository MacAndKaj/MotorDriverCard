/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformPollStatus.c
  * @brief          : Sources file.
  ******************************************************************************
  */

#include "msg/deserializers/PlatformPollStatus.h"

#include "main/defs.h"
#include <memory.h>

PlatformPollStatusReq* deserialize_PlatformPollStatusReq(char* data)
{
    PlatformPollStatusReq* msg = (PlatformPollStatusReq*)pvPortMalloc(sizeof(struct PlatformPollStatusReq));

    memcpy(msg, data, sizeof(struct PlatformPollStatusReq));
    return msg;
}

PlatformPollStatusResp* deserialize_PlatformPollStatusResp(char* data)
{
    PlatformPollStatusResp* msg = (PlatformPollStatusResp*)pvPortMalloc(sizeof(struct PlatformPollStatusResp));

    memcpy(msg, data, sizeof(struct PlatformPollStatusResp));
    return msg;
}
