/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <modules/controller/impl/controller.h>

#include <modules/log/interface.h>
#include <modules/controller/impl/defs.h>
#include <modules/controller/impl/message_dispatch.h>
#include <modules/controller/impl/motor_process.h>
#include <modules/controller/impl/pid.h>
#include <modules/controller/impl/handlers/platform_set_motor_speed_req_handler.h>
#include <main/defs.h>
#include <msg/defs/Message.h>

#include <math.h>
#include <string.h>

void handle_new_speed(struct controller_internal_data *handle, double leftSpeed, double rightSpeed);
void control_motor(struct motor_control_info *handle, const bool leftOrRight);

void controller_init(struct controller_data *data)
{
    struct controller_internal_data* handle = data->internal_data;
    handle->left_motor_control_info.pid_data = create_pid(4000., 150., 30.);
    handle->left_motor_control_info.pwm_period = PWM_PERIOD;
    handle->left_motor_control_info.stop_threshold = STOP_THRESHOLD;
    handle->left_motor_control_info.current_values.ref_speed = 0;
    handle->left_motor_control_info.motor_info_handle = data->left_motor_info;

    handle->right_motor_control_info.pid_data = create_pid(4000., 150., 30.);
    handle->right_motor_control_info.pwm_period = PWM_PERIOD;
    handle->right_motor_control_info.stop_threshold = STOP_THRESHOLD;
    handle->right_motor_control_info.current_values.ref_speed = 0;
    handle->right_motor_control_info.motor_info_handle = data->right_motor_info;

    motor_process_init(&handle->left_motor_control_info, &handle->right_motor_control_info);

    platform_set_motor_speed_req_handler_configure(handle, handle_new_speed);
}

void controller_work(struct controller_data *data)
{
    struct controller_internal_data* handle = data->internal_data;
    Message message_buffer;
    struct SpeedValues speed_values_buffer;
    memset(&message_buffer, 0, sizeof(Message));
    memset(&speed_values_buffer, 0, sizeof(struct SpeedValues));

    if (osMessageQueueGet(*data->speed_values_queue_handle, &speed_values_buffer, 0, 0) == osOK)
    {
        handle->left_motor_control_info.current_values.current_speed = speed_values_buffer.leftMotorSpeed;
        handle->right_motor_control_info.current_values.current_speed = speed_values_buffer.rightMotorSpeed;
    }

    if (osMessageQueueGet(*data->message_queue_handle, &message_buffer, 0, 0) == osOK)
    {
        LOG_INFO("New message received\n");
        dispatch_message(&message_buffer);
    }


    static bool left = true, right = false;
    control_motor(&handle->left_motor_control_info, left);
    control_motor(&handle->right_motor_control_info, right);
    
    osThreadYield();
}

void control_motor(struct motor_control_info *handle, const bool leftOrRight)
{
    double ctrl_err;
    int64_t u;

    if (fabs(handle->current_values.ref_speed) < 1.)
    {
        motor_process_update_u(handle, 0, leftOrRight);
        return;
    }

    ctrl_err = handle->current_values.ref_speed - handle->current_values.current_speed;
    u = (int64_t)pid_evaluate(&handle->pid_data, ctrl_err, SPEED_UPDATE_PERIOD);
    motor_process_update_u(handle, u, leftOrRight);
}

void handle_new_speed(struct controller_internal_data *handle, double leftSpeed, double rightSpeed)
{
    LOG_INFO_ARGS("Current speed: l-%0.3f, r-%0.3f\n", 
        handle->left_motor_control_info.current_values.current_speed,
        handle->right_motor_control_info.current_values.current_speed);
    LOG_INFO_ARGS("New speed: l-%0.3f, r-%0.3f\n", leftSpeed, rightSpeed);
    handle->left_motor_control_info.current_values.ref_speed = leftSpeed;
    handle->right_motor_control_info.current_values.ref_speed = rightSpeed;
}
