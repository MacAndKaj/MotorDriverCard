/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatforPollStatus.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_MSG_DEFS_DESERIALIZERS_PLATFORMPOLLSTATUS_H
#define MDC_MSG_DEFS_DESERIALIZERS_PLATFORMPOLLSTATUS_H

#include "msg/defs/PlatformPollStatus.h"

PlatformPollStatusReq* deserialize_PlatformPollStatusReq(char* data);
PlatformPollStatusResp* deserialize_PlatformPollStatusResp(char* data);

#endif //MDC_MSG_DEFS_DESERIALIZERS_PLATFORMPOLLSTATUS_H
