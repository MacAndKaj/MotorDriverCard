/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorSpeed.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_MSG_DEFS_PLATFORMSETMOTORSPEED_H
#define MOTORDRIVER_MSG_DEFS_PLATFORMSETMOTORSPEED_H

#include "msg/consts.h"

#include <stdint.h>

/*
 * lSpeedF/rSpeedF - fraction part of speed values
 * lSpeedI/rSpeedI - integer part of speed values
 */
struct PlatformSetMotorSpeedReq
{
    int8_t lSpeedI;
    uint8_t lSpeedF;
    int8_t rSpeedI;
    uint8_t rSpeedF;
};
typedef struct PlatformSetMotorSpeedReq PlatformSetMotorSpeedReq;

struct PlatformSetMotorSpeedResp
{
    enum Status status;
};
typedef struct PlatformSetMotorSpeedResp PlatformSetMotorSpeedResp;

#endif //MOTORDRIVER_MSG_DEFS_PLATFORMSETMOTORSPEED_H
