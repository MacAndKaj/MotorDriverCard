/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : monitoring.c
  * @brief          : Sources for motor.h file.
  ******************************************************************************
  */
#include <modules/monitoring/impl/monitoring.h>

#include <main/defs.h>
#include <modules/log/interface.h>
#include <msg/defs/Message.h>
#include <msg/message_ids.h>

#include <math.h>

#define POLL_STATUS_BIT_SPEED 0x01
#define POLL_STATUS_BIT_MODULE 0x02

void handle_status_polling(struct monitoring_data *handle, const struct PlatformPollStatusReq *req);
int8_t get_integral_speed_part(double speed);
uint8_t get_fractional_speed_part(double speed);

struct monitoring_internal_data
{
    struct SpeedValues speed_values_cache;
};

void monitoring_init(struct monitoring_data *handle)
{
    static struct monitoring_internal_data storage;
    storage.speed_values_cache.leftMotorSpeed = 0;
    storage.speed_values_cache.rightMotorSpeed = 0;
    handle->internal_data = &storage;
}

void monitoring_work(struct monitoring_data *handle)
{
    struct InternalMessage int_msg;
    if (osMessageQueueGet(*handle->internal_message_queue_handle, &int_msg, 0, 0) == osOK)
    {
        if (int_msg.msg_id == SPEED_VALUES_MSG_ID)
        {
            handle->internal_data->speed_values_cache = int_msg.speed_values;
        }
    }

    struct Message msg;
    if (osMessageQueueGet(*handle->syscom_message_queue_handle, &msg, 0, 0) == osOK)
    {
        switch (msg.messageId)
        {
        case PLATFORM_POLL_STATUS_REQ_ID:
            handle_status_polling(handle, &msg.msg.platformPollStatusReq);
            break;
        default:
            break;
        }
    }
    osThreadYield();
}

void handle_status_polling(struct monitoring_data *handle, const struct PlatformPollStatusReq *req)
{
    struct Message msg;
    if (req->statusSet & POLL_STATUS_BIT_SPEED)
    {
        const struct SpeedValues *speed = &handle->internal_data->speed_values_cache;
        msg.msg.platformPollStatusResp.lSpeedI = get_integral_speed_part(speed->leftMotorSpeed);
        msg.msg.platformPollStatusResp.lSpeedF = get_fractional_speed_part(speed->leftMotorSpeed);
        msg.msg.platformPollStatusResp.rSpeedI = get_integral_speed_part(speed->rightMotorSpeed);
        msg.msg.platformPollStatusResp.rSpeedF = get_fractional_speed_part(speed->rightMotorSpeed);
    }
    msg.messageId = PLATFORM_POLL_STATUS_RESP_ID;

    handle->send_syscom_message(&msg);
}

int8_t get_integral_speed_part(double speed)
{
    return (int8_t)speed;
}

uint8_t get_fractional_speed_part(double speed)
{
    uint8_t s1 = (uint8_t)(fabs(speed) * 100.f);
    uint8_t s2 = (uint8_t)(fabs(speed));
    return s1 - s2;
}