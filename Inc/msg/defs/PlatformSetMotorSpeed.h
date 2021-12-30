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

#include <msg/consts.h>

#include <stdint.h>

/*
 * lMotor/rMotor - should be set to 1 if values for right/left motor sent, 0 otherwise
 * lSpeedF/rSpeedF - fraction part of speed values
 * lSpeedI/rSpeedI - integer part of speed values
 */
struct PlatformSetMotorSpeedReq
{
    uint8_t lMotor;
    int8_t lSpeedI;
    uint8_t lSpeedF;
    uint8_t rMotor;
    int8_t rSpeedI;
    uint8_t rSpeedF;
};
typedef struct PlatformSetMotorSpeedReq PlatformSetMotorSpeedReq;

struct PlatformSetMotorSpeedResp
{
    uint8_t motor;
    enum Status status;
};
typedef struct PlatformSetMotorSpeedResp PlatformSetMotorSpeedResp;

#endif //MOTORDRIVER_MSG_DEFS_PLATFORMSETMOTORSPEED_H
