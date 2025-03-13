/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motor.c
  * @brief          : Sources for motor.h file.
  ******************************************************************************
  */
#include <modules/feedback/impl/feedback.h>

#include <main/defs.h>
#include <modules/log/interface.h>
#include <modules/feedback/interface.h>
#include <modules/feedback/impl/defs.h>
#include <modules/feedback/impl/encoder.h>

void feedback_start(struct feedback_data *handle)
{
    encoder_init_new(handle->left_encoder_data);
    encoder_init_new(handle->right_encoder_data);
    LOG_INFO("[feedback]Encoders started\n");
}

void feedback_work(struct feedback_data *handle)
{
    struct InternalMessage values;
    values.msg_id = SPEED_VALUES_MSG_ID;
    values.speed_values.leftMotorSpeed = get_speed(handle->left_encoder_data);
    values.speed_values.rightMotorSpeed = get_speed(handle->right_encoder_data);

    struct message_subscription *subscription = handle->subs;
    for (int i = 0; i < handle->subs_len; i++)
    {
        if (subscription->msg_id == SPEED_VALUES_MSG_ID)
        {
            osStatus_t status = osMessageQueuePut(*subscription->subscription_queue, &values, 0, 0);
            if (status != osOK)
            {
                LOG_INFO_ARGS("[feedback]Failed to send:%d\n", status);
            }
        }
        ++subscription;
    }
}

void feedback_update(struct feedback_data *handle)
{
    encoder_update(handle->left_encoder_data, SPEED_UPDATE_PERIOD);
    encoder_update(handle->right_encoder_data, SPEED_UPDATE_PERIOD);
    osThreadFlagsSet(*handle->feedback_thread_handle, PROBING_TIMEOUT_CALLBACK);
}
