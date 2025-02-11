/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_control.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include "modules/log/interface.h"
#include "main/defs.h"
#include "msg/consts.h"
#include "msg/message_ids.h"
#include "msg/defs/Message.h"
#include "msg/defs/Frame.h"
#include "msg/deserializers/PlatformPollStatus.h"
#include "msg/deserializers/PlatformSetMotorSpeed.h"
#include "msg/deserializers/PlatformSetMotorPwmValue.h"
#include "msg/serializers/PlatformSetMotorSpeed.h"

#include <stddef.h>
#include <string.h>

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
    static struct Message message;
    memset(&message, 0, sizeof(struct Message));
    message.messageId = id;
    switch (id)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            LOG_INFO("[rx] PLATFORM_SET_MOTOR_SPEED_REQ\n");
            message.msg.platformSetMotorSpeedReq = *deserialize_PlatformSetMotorSpeedReq(data);
            return &message;
        case PLATFORM_SET_MOTOR_PWM_VALUE_REQ_ID:
            LOG_INFO("[rx] PLATFORM_SET_MOTOR_PWM_VALUE_REQ_ID\n");
            message.msg.platformSetMotorPwmValueReq = *deserialize_PlatformSetMotorPwmValueReq(data);
            return &message;
        case PLATFORM_POLL_STATUS_REQ_ID:
            LOG_INFO("[rx] PLATFORM_POLL_STATUS_REQ_ID\n");
            message.msg.platformPollStatusReq = *deserialize_PlatformPollStatusReq(data);
            return &message;
        default:
            LOG_INFO("[rx] Unknown message\n");
            break;
    }
    return NULL;
}

struct Message* processFrame(const Frame* f)
{
    if (f->header != HEADER_BYTE)
    {
        LOG_INFO_ARGS("[rx] Frame Header incorrect! Value: %d\n", f->header);
        return NULL;
    }

    uint8_t messageId = f->id;
    if (messageId == 0)
    {
        LOG_INFO_ARGS("[rx] Incorrect message ID! Value: %d\n", f->id);
        return NULL;
    }

    struct Message* deserializedMsg = deserialize((char*)f->data, messageId);

    if (deserializedMsg == NULL)
    {
        LOG_INFO("[rx] Deserialization failed\n");
    }

    return deserializedMsg;
}

struct Message* processData(const uint8_t* frame_data)
{
    union {
        uint8_t serializedFrame[FRAME_SIZE];
        Frame deserializedFrame;
    } buf;
    memcpy(buf.serializedFrame, frame_data, FRAME_SIZE);
    return processFrame(&buf.deserializedFrame);
}
