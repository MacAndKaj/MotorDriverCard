/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.h
  * @brief          : Header for serializers of PlatformSetMotorSpeedReq/Resp.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_COM_INTERFACE_SER_DES_SERIALIZERS_PLATFORMSETMOTORSPEED_H
#define MOTORDRIVER_COM_INTERFACE_SER_DES_SERIALIZERS_PLATFORMSETMOTORSPEED_H

#include "msg/defs/PlatformSetMotorSpeed.h"

void serialize_PlatformSetMotorSpeedResp(const PlatformSetMotorSpeedResp* resp, uint8_t *out_buf);

#endif //MOTORDRIVER_COM_INTERFACE_SER_DES_SERIALIZERS_PLATFORMSETMOTORSPEED_H
