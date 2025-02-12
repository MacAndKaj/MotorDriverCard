/**
  * Copyright (c) 2023 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorPwmValue.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_COM_INTERFACE_SER_DES_DESERIALIZERS_PLATFORMSETMOTORPWMVALUE_H
#define MOTORDRIVER_COM_INTERFACE_SER_DES_DESERIALIZERS_PLATFORMSETMOTORPWMVALUE_H

#include "msg/defs/PlatformSetMotorPwmValue.h"

PlatformSetMotorPwmValueReq* deserialize_PlatformSetMotorPwmValueReq(char* data);
PlatformSetMotorPwmValueResp* deserialize_PlatformSetMotorPwmValueResp(char* data);

#endif //MOTORDRIVER_COM_INTERFACE_SER_DES_DESERIALIZERS_PLATFORMSETMOTORPWMVALUE_H
