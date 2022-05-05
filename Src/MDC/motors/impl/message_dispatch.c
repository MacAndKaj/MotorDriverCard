/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_dispatch.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <MDC/motors/impl/message_dispatch.h>

#include <MDC/log/interface.h>
#include <MDC/motors/impl/handlers/platform_set_motor_speed_req_handler.h>
#include <msg/defs/Message.h>
#include <msg/message_ids.h>

void message_dispatch_onMessageReceived(const Message* msg)
{
    switch (msg->messageId)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            {
                logInfo("[motors] Message PLATFORM_SET_MOTOR_SPEED_REQ received.");
                platform_set_motor_speed_req_handler_handle(&msg->msg.platformSetMotorSpeedReq);
                break;
            }
        default:
            logInfo("Unknown messageId, ignoring!");
    }
}