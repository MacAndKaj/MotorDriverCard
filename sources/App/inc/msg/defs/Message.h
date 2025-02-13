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

struct Message
{
    uint8_t messageId;
    union
    {
        PlatformSetMotorSpeedReq      platformSetMotorSpeedReq;
        PlatformSetMotorSpeedResp     platformSetMotorSpeedResp;
        PlatformSetMotorPwmValueReq   platformSetMotorPwmValueReq;
        PlatformSetMotorPwmValueResp  platformSetMotorPwmValueResp;
        PlatformPollStatusReq         platformPollStatusReq;
        PlatformPollStatusResp        platformPollStatusResp;
    } msg;
};
typedef struct Message Message;

#endif //MOTORDRIVER_COM_INTERFACE_DEFS_MESSAGE_H
