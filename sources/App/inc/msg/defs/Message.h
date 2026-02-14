/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : Message.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_COM_INTERFACE_DEFS_MESSAGE_H
#define MOTORDRIVER_COM_INTERFACE_DEFS_MESSAGE_H

#include "msg/defs/PlatformPollStatus.h"
#include "msg/defs/PlatformSetMotorSpeed.h"
#include "msg/defs/PlatformSetMotorPwmValue.h"
#include "msg/defs/PlatformStatus.h"

struct Message
{
    uint8_t messageId;
    union
    {
        PlatformSetMotorSpeedReq      platformSetMotorSpeedReq; // deprecated
        PlatformSetMotorSpeedResp     platformSetMotorSpeedResp;// deprecated
        PlatformSetMotorPwmValueReq   platformSetMotorPwmValueReq;// deprecated
        PlatformSetMotorPwmValueResp  platformSetMotorPwmValueResp;// deprecated
        PlatformPollStatusReq         platformPollStatusReq;// deprecated
        PlatformPollStatusResp        platformPollStatusResp;// deprecated
        PlatformSetMotorSpeedReq      cmd_set_motor_speed;
        PlatformSetMotorPwmValueReq   cmd_set_motor_pwm_value;
        PlatformStatus                platform_status;
    } msg;
};
typedef struct Message Message;

#endif //MOTORDRIVER_COM_INTERFACE_DEFS_MESSAGE_H
