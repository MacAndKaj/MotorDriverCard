/**
  * Copyright (c) 2023 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformSetMotorPwmValue.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_MSG_DEFS_PLATFORMSETMOTORMOTORVALUE_H
#define MOTORDRIVER_MSG_DEFS_PLATFORMSETMOTORMOTORVALUE_H

#include "msg/consts.h"

#include <stdint.h>

/*
 * ONLY FOR DEBUGGING PURPOSES
 * lPwmValue - value of PWM duty for left motor
 * rPwmValue - value of PWM duty for right motor
 * lDirection - direction of left motor rotation 0-forward/0-backward
 * rDirection - direction of right motor rotation 0-forward/0-backward
 */
struct PlatformSetMotorPwmValueReq
{
    uint32_t lPwmValue;
    uint32_t rPwmValue;
    uint8_t lDirection;
    uint8_t rDirection;
};
typedef struct PlatformSetMotorPwmValueReq PlatformSetMotorPwmValueReq;

/*
 * status - status of setting the value
 */
struct PlatformSetMotorPwmValueResp
{
    enum Status status;
};
typedef struct PlatformSetMotorPwmValueResp PlatformSetMotorPwmValueResp;

#endif //MOTORDRIVER_MSG_DEFS_PLATFORMSETMOTORMOTORVALUE_H
