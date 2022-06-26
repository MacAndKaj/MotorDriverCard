/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <MDC/controller/impl/pid.h>
#include <MDC/controller/impl/motor_process.h>
#include <MDC/controller/impl/defs.h>
#include <MDC/controller/impl/message_dispatch.h>
#include <MDC/main/defs.h>

#include <log/interface.h>
#include <msg/defs/Message.h>

#include <gpio.h>

#include <cmsis_os2.h>
#include <MDC/controller/impl/handlers/platform_set_motor_speed_req_handler.h>

typedef struct
{
    double refSpeed;
} CurrentValues;

typedef struct
{
    struct OutputConfiguration controlConfiguration;
    struct PIDParameters controllerParameters;
    CurrentValues currentValues;
} MotorConfiguration;

static struct
{
    MotorConfiguration leftMotorConfiguration;
    MotorConfiguration rightMotorConfiguration;
    osMessageQueueId_t* messageQueueHandle;
    osThreadId_t* threadIdHandle;
} motorsContext;

void control();

void configure_controller_impl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    motorsContext.messageQueueHandle = messageQueueHandle;
    motorsContext.threadIdHandle = threadIdHandle;
    motorsContext.rightMotorConfiguration.currentValues.refSpeed = 0;
    motorsContext.leftMotorConfiguration.currentValues.refSpeed = 0;
    motorsContext.leftMotorConfiguration.controllerParameters = create_pid(4000., 150., 30.);
    motorsContext.rightMotorConfiguration.controllerParameters = create_pid(4000., 150., 30.);

    struct OutputConfiguration leftMotorConfig = {
        .stopThreshold = STOP_THRESHOLD,
        .pwmPeriod = PWM_PERIOD,
        .motorControl1Port = LeftMotorIn1_GPIO_Port,
        .motorControl1Pin = LeftMotorIn1_Pin,
        .motorControl2Port = LeftMotorIn2_GPIO_Port,
        .motorControl2Pin = LeftMotorIn2_Pin,
        .timer = &htim2,
        .channel = TIM_CHANNEL_3,
    };
    motorsContext.leftMotorConfiguration.controlConfiguration = leftMotorConfig;

    struct OutputConfiguration rightMotorConfig = {
        .stopThreshold = STOP_THRESHOLD,
        .pwmPeriod = PWM_PERIOD,
        .motorControl1Port = RightMotorIn1_GPIO_Port,
        .motorControl1Pin = RightMotorIn1_Pin,
        .motorControl2Port = RightMotorIn2_GPIO_Port,
        .motorControl2Pin = RightMotorIn2_Pin,
        .timer = &htim3,
        .channel = TIM_CHANNEL_1,
    };
    motorsContext.rightMotorConfiguration.controlConfiguration = rightMotorConfig;

    motor_process_configure(&motorsContext.leftMotorConfiguration.controlConfiguration,
                            &motorsContext.rightMotorConfiguration.controlConfiguration);

    platform_set_motor_speed_req_handler_configure(&motorsContext.leftMotorConfiguration.currentValues.refSpeed,
                                                   &motorsContext.rightMotorConfiguration.currentValues.refSpeed);
}

void work_controller_impl()
{
    static Message buffer;
    if (osMessageQueueGet(*motorsContext.messageQueueHandle, &buffer, 0, 0) == osOK)
    {
        LOG_INFO("New message to motors");
        dispatch_message(&buffer);
    }

    control();
    osThreadYield();
}

void control()
{
    static bool left = true, right = false;
    double leftControlError, rightControlError;
    int64_t uLeft, uRight;

    leftControlError = motorsContext.leftMotorConfiguration.currentValues.refSpeed -
                       get_speed(&motorsContext.leftMotorConfiguration.feedbackConfiguration);
    rightControlError = motorsContext.rightMotorConfiguration.currentValues.refSpeed -
                        get_speed(&motorsContext.rightMotorConfiguration.feedbackConfiguration);

    uLeft = pid_evaluate(&motorsContext.leftMotorConfiguration.controllerParameters,
                         leftControlError,
                         SPEED_UPDATE_PERIOD);
    uRight = pid_evaluate(&motorsContext.rightMotorConfiguration.controllerParameters,
                          rightControlError,
                          SPEED_UPDATE_PERIOD);

    motor_process_update_u(&motorsContext.leftMotorConfiguration.controlConfiguration, uLeft, left);
    motor_process_update_u(&motorsContext.rightMotorConfiguration.controlConfiguration, uRight, right);
}
