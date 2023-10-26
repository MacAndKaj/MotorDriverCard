/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_control.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include "log/interface.h"
#include "main/defs.h"
#include "msg/consts.h"
#include "msg/messages_size_map.h"
#include "msg/defs/Message.h"
#include "msg/defs/Frame.h"
#include "msg/ser_des/deserializers/PlatformSetMotorSpeed.h"
#include "msg/ser_des/serializers/PlatformSetMotorSpeed.h"

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
            LOG_INFO("PLATFORM_SET_MOTOR_SPEED_REQ received\n");
            message.msg.platformSetMotorSpeedReq = *deserialize_PlatformSetMotorSpeedReq(data);
            return &message;
        default:
            LOG_INFO("Unknown message\n");
            break;
    }
    return NULL;
}

typedef union {
    uint8_t serializedFrame[FRAME_SIZE];
    Frame deserializedFrame;
} ConvertBuffer;



struct Message* processFrame(const Frame* f)
{
    if (f->header != HEADER_BYTE)
    {
        LOG_INFO_ARGS("Frame Header incorrect! Value: %d\n", f->header);
        return NULL;
    }

    uint8_t messageId = f->id;
    if (messageId == 0)
    {
        LOG_INFO_ARGS("Incorrect message ID! Value: %d\n", f->id);
        return NULL;
    }

    struct Message* deserializedMsg = deserialize((char*)f->data, messageId);

    if (deserializedMsg == NULL)
    {
        LOG_INFO("Deserialization failed\n");
    }

    return deserializedMsg;
}

struct Message* processData(const uint8_t* frame_data)
{
    ConvertBuffer buf;
    memcpy(buf.serializedFrame, frame_data, FRAME_SIZE);
    return processFrame(&buf.deserializedFrame);
}
