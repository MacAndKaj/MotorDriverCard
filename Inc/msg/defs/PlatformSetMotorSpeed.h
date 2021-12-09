/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_COM_INTERFACE_DEFS_PLATFORMSETMOTORSPEED_H
#define MOTORDRIVER_COM_INTERFACE_DEFS_PLATFORMSETMOTORSPEED_H

#include <msg/consts.h>

#include <stdint.h>

struct PlatformSetMotorSpeedReq
{
    //TODO: multimotor option
    uint8_t motor;
    int8_t speedI;
    uint8_t speedF;
};
typedef struct PlatformSetMotorSpeedReq PlatformSetMotorSpeedReq;

struct PlatformSetMotorSpeedResp
{
    uint8_t motor;
    enum Status status;
};
typedef struct PlatformSetMotorSpeedResp PlatformSetMotorSpeedResp;

#endif //MOTORDRIVER_COM_INTERFACE_DEFS_PLATFORMSETMOTORSPEED_H
