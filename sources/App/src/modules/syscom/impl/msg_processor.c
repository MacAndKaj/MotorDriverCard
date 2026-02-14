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
#include "msg/defs/PlatformStatus.h"
#include "msg/deserializers/PlatformPollStatus.h"
#include "msg/deserializers/PlatformSetMotorSpeed.h"
#include "msg/deserializers/PlatformSetMotorPwmValue.h"
#include "msg/serializers/PlatformPollStatus.h"
#include "msg/serializers/PlatformSetMotorSpeed.h"
#include "msg/serializers/PlatformStatus.h"

#include <stddef.h>
#include <string.h>

typedef union {
    uint8_t serializedFrame[FRAME_SIZE];
    Frame deserializedFrame;
} ConvertingBuffer;

void serialize(const Message* msg, uint8_t *out_buf)
{
    switch (msg->messageId)
    {
        case PLATFORM_SET_MOTOR_SPEED_RESP_ID:
            memcpy(out_buf, &msg->msg, sizeof(struct PlatformSetMotorSpeedResp));
            break;
        case PLATFORM_POLL_STATUS_RESP_ID:
            memcpy(out_buf, &msg->msg, sizeof(struct PlatformPollStatusResp));
            break;
        case PLATFORM_STATUS_MSG_ID:
            memcpy(out_buf, &msg->msg, sizeof(PlatformStatus));
            break;
        default:
            LOG_INFO("[tx] Unknown message for serialization\n");
            break;
    }
}

Message* deserialize(char* data, uint8_t id)
{
    static Message message = {0};
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
    case CMD_SET_MOTOR_SPEED_ID:
        message.msg.cmd_set_motor_speed = *deserialize_PlatformSetMotorSpeedReq(data);
        return &message;
    case CMD_SET_MOTOR_PWM_VALUE_ID:
        message.msg.cmd_set_motor_pwm_value = *deserialize_PlatformSetMotorPwmValueReq(data);
        return &message;
    default:
        LOG_INFO("[rx] Unknown message\n");
        break;
    }
    return NULL;
}

Message* processFrame(const Frame* f)
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

    if (messageId == HEARTBEAT_MSG_ID)
    {
        // restart heartbeat timer
        return NULL;
    }

    Message* deserializedMsg = deserialize((char*)f->data, messageId);

    if (deserializedMsg == NULL)
    {
        LOG_INFO("[rx] Deserialization failed\n");
    }

    return deserializedMsg;
}

Message* process_data(const uint8_t* frame_data)
{
    ConvertingBuffer buf;
    memcpy(buf.serializedFrame, frame_data, FRAME_SIZE);
    return processFrame(&buf.deserializedFrame);
}

void prepare_frame(const Message* status, uint8_t* out_buf)
{
    if (status->messageId != PLATFORM_STATUS_MSG_ID)
    {
        LOG_INFO("[tx] Incorrect message for preparing frame\n");
        return;
    }
    ConvertingBuffer buf;
    buf.deserializedFrame = (Frame){
        .header = HEADER_BYTE,
        .id = PLATFORM_STATUS_MSG_ID,
        .crc = 0 // TODO: calculate crc
    };

    serialize(status, buf.deserializedFrame.data);
    memcpy(out_buf, buf.serializedFrame, FRAME_SIZE);
}

void convert_speed_values_to_status(const struct SpeedValues* speed_values, PlatformStatus* status)
{
    status->l_speed_i = (int8_t)speed_values->leftMotorSpeed;
    status->l_speed_f = (uint8_t)((speed_values->leftMotorSpeed - status->l_speed_i) * 100);
    status->r_speed_i = (int8_t)speed_values->rightMotorSpeed;
    status->r_speed_f = (uint8_t)((speed_values->rightMotorSpeed - status->r_speed_i) * 100);
}

void process_message(const struct InternalMessage *src_msg, PlatformStatus* dest_msg)
{
    switch (src_msg->msg_id)
    {
    case SPEED_VALUES_MSG_ID:
        convert_speed_values_to_status(&src_msg->speed_values, dest_msg);
        break;
    default:
        LOG_INFO("[tx] Unknown message for processing\n");
        break;
    }
}