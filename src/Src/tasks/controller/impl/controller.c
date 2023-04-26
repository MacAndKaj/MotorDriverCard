/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <log/interface.h>
#include <tasks/controller/impl/pid.h>
#include <tasks/controller/impl/motor_process.h>
#include <tasks/controller/impl/defs.h>
#include <tasks/controller/impl/message_dispatch.h>
#include <tasks/controller/impl/handlers/platform_set_motor_speed_req_handler.h>
#include <main/defs.h>
#include <msg/defs/Message.h>

#include <gpio.h>
#include <string.h>

#include <cmsis_os2.h>

typedef struct
{
    struct OutputConfiguration controlConfiguration;
    struct PIDParameters controllerParameters;
    double m_refSpeed;
    double m_currentSpeed;
} MotorConfiguration;

static struct
{
    MotorConfiguration leftMotorConfiguration;
    MotorConfiguration rightMotorConfiguration;
    osMessageQueueId_t* m_messageQueueHandle;
    osMessageQueueId_t* m_speedValuesQueueHandle;
    osThreadId_t* threadIdHandle;
} motorsContext;

void control();
void handle_new_speed(double leftSpeed, double rightSpeed);

void configure_controller_impl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle, osMessageQueueId_t* speedValuesQueueHandle)
{
    motorsContext.m_messageQueueHandle = messageQueueHandle;
    motorsContext.m_speedValuesQueueHandle = speedValuesQueueHandle;
    motorsContext.threadIdHandle = threadIdHandle;
    motorsContext.rightMotorConfiguration.m_refSpeed = 0;
    motorsContext.leftMotorConfiguration.m_refSpeed = 0;
    motorsContext.leftMotorConfiguration.controllerParameters = create_pid(4000., 150., 30.);
    motorsContext.rightMotorConfiguration.controllerParameters = create_pid(4000., 150., 30.);

    motorsContext.leftMotorConfiguration.controlConfiguration.stopThreshold = STOP_THRESHOLD;
    motorsContext.leftMotorConfiguration.controlConfiguration.pwmPeriod = PWM_PERIOD;
    motorsContext.leftMotorConfiguration.controlConfiguration.motorControl1Port = LeftMotorIn1_GPIO_Port;
    motorsContext.leftMotorConfiguration.controlConfiguration.motorControl1Pin = LeftMotorIn1_Pin;
    motorsContext.leftMotorConfiguration.controlConfiguration.motorControl2Port = LeftMotorIn2_GPIO_Port;
    motorsContext.leftMotorConfiguration.controlConfiguration.motorControl2Pin = LeftMotorIn2_Pin;
    motorsContext.leftMotorConfiguration.controlConfiguration.timer = &htim2;
    motorsContext.leftMotorConfiguration.controlConfiguration.channel = TIM_CHANNEL_3;

    motorsContext.rightMotorConfiguration.controlConfiguration.stopThreshold = STOP_THRESHOLD;
    motorsContext.rightMotorConfiguration.controlConfiguration.pwmPeriod = PWM_PERIOD;
    motorsContext.rightMotorConfiguration.controlConfiguration.motorControl1Port = RightMotorIn1_GPIO_Port;
    motorsContext.rightMotorConfiguration.controlConfiguration.motorControl1Pin = RightMotorIn1_Pin;
    motorsContext.rightMotorConfiguration.controlConfiguration.motorControl2Port = RightMotorIn2_GPIO_Port;
    motorsContext.rightMotorConfiguration.controlConfiguration.motorControl2Pin = RightMotorIn2_Pin;
    motorsContext.rightMotorConfiguration.controlConfiguration.timer = &htim3;
    motorsContext.rightMotorConfiguration.controlConfiguration.channel = TIM_CHANNEL_1;

    motor_process_configure(&motorsContext.leftMotorConfiguration.controlConfiguration,
                            &motorsContext.rightMotorConfiguration.controlConfiguration);

    platform_set_motor_speed_req_handler_configure(handle_new_speed);
}

void work_controller_impl()
{
    Message messageBuffer;
    memset(&messageBuffer, 0, sizeof(Message));
    struct SpeedValues speedValuesBuffer;
    memset(&speedValuesBuffer, 0, sizeof(struct SpeedValues));

    if (osMessageQueueGet(*motorsContext.m_speedValuesQueueHandle, &speedValuesBuffer, 0, 0) == osOK)
    {
        motorsContext.leftMotorConfiguration.m_currentSpeed = speedValuesBuffer.leftMotorSpeed;
        motorsContext.rightMotorConfiguration.m_currentSpeed = speedValuesBuffer.rightMotorSpeed;
    }

    if (osMessageQueueGet(*motorsContext.m_messageQueueHandle, &messageBuffer, 0, 0) == osOK)
    {
        LOG_INFO("New message received\n");
        dispatch_message(&messageBuffer);
    }

    control();
    osThreadYield();
}

void control_motor(MotorConfiguration* m, const bool leftOrRight)
{
    double controlError;
    int64_t u;

    controlError = m->m_refSpeed - m->m_currentSpeed;
    u = (int64_t)pid_evaluate(&m->controllerParameters, controlError, SPEED_UPDATE_PERIOD);
    motor_process_update_u(&m->controlConfiguration, u, leftOrRight);
}

void control()
{
    static bool left = true, right = false;
    control_motor(&motorsContext.leftMotorConfiguration, left);
    control_motor(&motorsContext.rightMotorConfiguration, right);
}

void handle_new_speed(double leftSpeed, double rightSpeed)
{
    motorsContext.leftMotorConfiguration.m_refSpeed = leftSpeed;
    motorsContext.rightMotorConfiguration.m_refSpeed = rightSpeed;
}
