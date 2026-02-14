/**
* Copyright (c) 2026 MacAndKaj. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformStatus.h
  * @brief          : Header for serializers of PlatformStatus.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_MSG_SERIALIZERS_PLATFORMSTATUS_H
#define MOTORDRIVER_MSG_SERIALIZERS_PLATFORMSTATUS_H

#include "msg/defs/PlatformStatus.h"

void serialize_PlatformStatus(const PlatformStatus* resp, uint8_t *out_buf);

#endif //MOTORDRIVER_MSG_SERIALIZERS_PLATFORMSTATUS_H
