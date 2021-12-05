/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_control.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/com/impl/message_control.h>

#include <msg/consts.h>
#include <msg/messages_size_map.h>
#include <msg/defs/Message.h>
#include <msg/ser_des/deserializers/PlatformSetMotorSpeed.h>
#include <msg/ser_des/serializers/PlatformSetMotorSpeed.h>

#include <cmsis_os2.h>

#include <stddef.h>
#include <malloc.h>
#include <stdio.h>

int validateCtrlData(MessageControl* messageControl, const uint8_t data[HEADER_SIZE])
{
    if (data[0] != FRAME_CTRL_DATA) return 1;

    return 0;
}

char* serialize(void* resp, uint8_t id)
{
    switch (id)
    {
        case PLATFORM_SET_MOTOR_SPEED_RESP_ID:
            return serialize_PlatformSetMotorSpeedResp((PlatformSetMotorSpeedResp*) resp);
    }
    return NULL;
}

Message* deserialize(char* data, uint8_t id)
{
    struct Message* message = malloc(sizeof(struct Message));
    message->messageId = id;
    switch (id)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            message->msg.platformSetMotorSpeedReq = *deserialize_PlatformSetMotorSpeedReq(data);
            return message;
        default:
            free(message);
    }
    return NULL;
}

void forwardMessage(MessageControl* messageControl, const Message* msg)
{
    printf("Forwarding message with id %d\r\n", msg->messageId);

    osStatus_t status = osMessageQueuePut(messageControl->interThreadComIfParams.messageQueueId, msg, 0, 0);
    if (status != osOK)
    {
//       printf("Error %d occurred when putting message to %s\r\n",
//              (int)status,
//              osMessageQueueGetName(messageControl->interThreadComIfParams.messageQueueId));
    }
    osEventFlagsSet(messageControl->interThreadComIfParams.messageReceivedFlagsId, FLAG_SET);
}