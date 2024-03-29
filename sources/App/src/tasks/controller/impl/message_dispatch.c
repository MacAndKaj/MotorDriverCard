/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_dispatch.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include "tasks/controller/impl/message_dispatch.h"

#include "log/interface.h"
#include "tasks/controller/impl/handlers/platform_set_motor_speed_req_handler.h"
#include "msg/defs/Message.h"
#include "msg/message_ids.h"

void dispatch_message(const Message* msg)
{
    switch (msg->messageId)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            {
                LOG_INFO("[motors] Message PLATFORM_SET_MOTOR_SPEED_REQ received.\n");
                platform_set_motor_speed_req_handler_handle(&msg->msg.platformSetMotorSpeedReq);
                break;
            }
        default:
            LOG_INFO("Unknown messageId, ignoring!\n");
    }
}