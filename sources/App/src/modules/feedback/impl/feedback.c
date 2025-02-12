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
    LOG_INFO("Encoders started\n");
}

void feedback_work(struct feedback_data *handle)
{
    static struct SpeedValues values;
    values.leftMotorSpeed = get_speed(handle->left_encoder_data);
    values.rightMotorSpeed = get_speed(handle->right_encoder_data);

    if (osMessageQueuePut(*handle->speed_meas_queue_handle, &values, 0, 0) != osOK)
    {
        LOG_INFO("Failed to put speed values to queue\n");
    }
}

void feedback_update(struct feedback_data *handle)
{
    encoder_update(handle->left_encoder_data, SPEED_UPDATE_PERIOD);
    encoder_update(handle->right_encoder_data, SPEED_UPDATE_PERIOD);
    osThreadFlagsSet(*handle->feedback_thread_handle, PROBING_TIMEOUT_CALLBACK);
}
