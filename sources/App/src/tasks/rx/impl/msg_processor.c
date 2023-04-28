/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_control.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */


#include "msg/consts.h"
#include "msg/messages_size_map.h"
#include "msg/defs/Message.h"
#include "msg/ser_des/deserializers/PlatformSetMotorSpeed.h"
#include "msg/ser_des/serializers/PlatformSetMotorSpeed.h"

#include <stddef.h>
#include "main/defs.h"
#include "log/interface.h"
#include <string.h>


struct
{
    uint8_t nextReadMessageId;
    uint16_t nextMessageSize;
    enum DataType nextDataType;
} msgControl;

enum DataType getNextDataType()
{
    return msgControl.nextDataType;
}

uint16_t getNextMessageSize()
{
    return msgControl.nextMessageSize;
}

void configureMsgProcessor()
{
    msgControl.nextDataType = FrameCtrlData;
    msgControl.nextReadMessageId = 0;
    msgControl.nextMessageSize = HEADER_SIZE;
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
    static struct Message message;
    memset(&message, 0, sizeof(struct Message));
    message.messageId = id;
    switch (id)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            message.msg.platformSetMotorSpeedReq = *deserialize_PlatformSetMotorSpeedReq(data);
            return &message;
        default:
            break;
    }
    return NULL;
}

void processFrameCtrlData(const uint8_t* data)
{
    if (data[0] != FRAME_CTRL_DATA)
    {
        msgControl.nextDataType = FrameCtrlData;
        msgControl.nextMessageSize = HEADER_SIZE;
        LOG_INFO("FrameCtrlData incorrect!\n");
        return;
    }
    msgControl.nextDataType = UserData;

    msgControl.nextReadMessageId = data[1];
    msgControl.nextMessageSize = findSizeForMessageId(msgControl.nextReadMessageId);
    if (msgControl.nextReadMessageId == 0)
    {
        msgControl.nextDataType = FrameCtrlData;
        msgControl.nextMessageSize = HEADER_SIZE;
        LOG_INFO("Unknown message!\n");
    }
}

struct Message* processUserData(uint8_t* data)
{
    struct Message* deserializedMsg = deserialize((char*)data,msgControl.nextReadMessageId);

    if (deserializedMsg == NULL)
    {
        LOG_INFO("Unknown user data\n");
    }
    msgControl.nextDataType = FrameCtrlData;
    msgControl.nextMessageSize = HEADER_SIZE;

    return deserializedMsg;
}