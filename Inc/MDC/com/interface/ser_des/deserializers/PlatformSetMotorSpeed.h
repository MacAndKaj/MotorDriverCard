/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_COM_INTERFACE_SER_DES_DESERIALIZERS_PLATFORMSETMOTORSPEED_H
#define MOTORDRIVER_COM_INTERFACE_SER_DES_DESERIALIZERS_PLATFORMSETMOTORSPEED_H

#include <MDC/com/interface/defs/PlatformSetMotorSpeed.h>

PlatformSetMotorSpeedReq* deserialize_PlatformSetMotorSpeedReq(char* data);
PlatformSetMotorSpeedResp* deserialize_PlatformSetMotorSpeedResp(char* data);

#endif //MOTORDRIVER_COM_INTERFACE_SER_DES_DESERIALIZERS_PLATFORMSETMOTORSPEED_H
