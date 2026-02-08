/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformPollStatus.h
  * @brief          : Header for serializers of PlatformPollStatusResp.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_COM_INTERFACE_SER_DES_SERIALIZERS_PLATFORMPOLLSTATUS_H
#define MOTORDRIVER_COM_INTERFACE_SER_DES_SERIALIZERS_PLATFORMPOLLSTATUS_H

#include "msg/defs/PlatformPollStatus.h"

void serialize_PlatformPollStatusResp(const PlatformPollStatusResp* resp, uint8_t *out_buf);

#endif //MOTORDRIVER_COM_INTERFACE_SER_DES_SERIALIZERS_PLATFORMPOLLSTATUS_H
