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

void handle_encoders_data(struct feedback_data *handle);
void handle_imu_data(struct feedback_data *handle);

void feedback_start(struct feedback_data *handle)
{
    encoder_init_new(handle->left_encoder_data);
    encoder_init_new(handle->right_encoder_data);
    LOG_INFO("[feedback]Encoders started\n");
}

void feedback_work(struct feedback_data *handle, uint8_t flag)
{
    switch (flag)
    {
    case PROBING_TIMEOUT_CALLBACK:
        handle_encoders_data(handle);
        break;
    case IMU_DATA_READY_FLAG:
        handle_imu_data(handle);
        break;
    default:
        LOG_INFO("[feedback]Unknown flag\n");
        break;
    }
}

void feedback_update(struct feedback_data *handle)
{
    encoder_update(handle->left_encoder_data, SPEED_UPDATE_PERIOD);
    encoder_update(handle->right_encoder_data, SPEED_UPDATE_PERIOD);
    osThreadFlagsSet(*handle->feedback_thread_handle, PROBING_TIMEOUT_CALLBACK);
}

void handle_encoders_data(struct feedback_data *handle)
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
            if (status != osOK && status != osErrorResource)
            {
                LOG_INFO_ARGS("[feedback]Failed to send Speed values:%d\n", status);
            }
        }
        ++subscription;
    }
}

void handle_imu_data(struct feedback_data *handle)
{
    struct InternalMessage values;
    values.msg_id = IMU_VALUES_MSG_ID;
    values.imu_values.acc_x = (int16_t)(handle->accel_and_gyro_data_buffer[0] << 8 | handle->accel_and_gyro_data_buffer[1]) * 1000 / 8192; // Convert to mm/s^2 assuming accelerometer is set to +-4g
    values.imu_values.acc_y = (int16_t)(handle->accel_and_gyro_data_buffer[2] << 8 | handle->accel_and_gyro_data_buffer[3]) * 1000 / 8192;
    values.imu_values.gyro_z = (int16_t)(handle->accel_and_gyro_data_buffer[12] << 8 | handle->accel_and_gyro_data_buffer[13]) * 1000 / 16.4; // Convert to rad/s * 1000 assuming gyroscope is set to +-2000 deg/s

    struct message_subscription *subscription = handle->subs;
    for (int i = 0; i < handle->subs_len; i++)
    {
        if (subscription->msg_id == IMU_VALUES_MSG_ID)
        {
            osStatus_t status = osMessageQueuePut(*subscription->subscription_queue, &values, 0, 0);
            if (status != osOK && status != osErrorResource)
            {
                LOG_INFO_ARGS("[feedback]Failed to send IMU values:%d\n", status);
            }
        }
        ++subscription;
    }
}
