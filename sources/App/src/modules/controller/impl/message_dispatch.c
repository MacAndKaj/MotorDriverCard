/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_dispatch.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <modules/controller/impl/message_dispatch.h>

#include <modules/log/interface.h>
#include <modules/controller/impl/handlers/platform_set_motor_speed_req_handler.h>
#include <modules/controller/impl/handlers/platform_set_motor_pwm_value_req_handler.h>
#include <msg/defs/Message.h>
#include <msg/message_ids.h>

void dispatch_message(const Message* msg)
{
    switch (msg->messageId)
    {
        case CMD_SET_MOTOR_SPEED_ID:
            {
                LOG_INFO("[controller] Message PLATFORM_SET_MOTOR_SPEED_REQ received.\n");
                platform_set_motor_speed_req_handler_handle(&msg->msg.cmd_set_motor_speed);
                break;
            }
        case CMD_SET_MOTOR_PWM_VALUE_ID:
            {
                LOG_INFO("[controller] Message PLATFORM_SET_MOTOR_PWM_VALUE_REQ_ID received.\n");
                platform_set_motor_pwm_value_req_handler_handle(&msg->msg.cmd_set_motor_pwm_value);
                break;
            }
        default:
            LOG_INFO("[controller] Unknown messageId, ignoring!\n");
    }
}