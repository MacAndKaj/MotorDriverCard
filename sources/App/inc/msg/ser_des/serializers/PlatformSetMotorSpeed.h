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

char* serialize_PlatformSetMotorSpeedReq(PlatformSetMotorSpeedReq* req);
char* serialize_PlatformSetMotorSpeedResp(PlatformSetMotorSpeedResp* resp);

#endif //MOTORDRIVER_COM_INTERFACE_SER_DES_SERIALIZERS_PLATFORMSETMOTORSPEED_H
