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
#include <MDC/controller/impl/feedback.h>
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
    struct FeedbackConfiguration feedbackConfiguration;
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

void periodical_callback_controller_impl()
{
    handle_feedback(&motorsContext.rightMotorConfiguration.feedbackConfiguration, SPEED_UPDATE_PERIOD);
    handle_feedback(&motorsContext.leftMotorConfiguration.feedbackConfiguration, SPEED_UPDATE_PERIOD);
    osThreadFlagsSet(*motorsContext.threadIdHandle, PROBING_TIMEOUT_CALLBACK);
}

void on_ext_interrupt_controller_impl(uint16_t GPIO_Pin)
{
    bool left = true, right = false;
    switch (GPIO_Pin)
    {
        case LeftMotorEncoderB_Pin:
            update_feedback(&motorsContext.rightMotorConfiguration.feedbackConfiguration, left);
            break;
        case RightMotorEncoderB_Pin:
            update_feedback(&motorsContext.rightMotorConfiguration.feedbackConfiguration, right);
            break;
        default:
            break;
    }
}

void control();

void configure_motors_impl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    motorsContext.messageQueueHandle = messageQueueHandle;
    motorsContext.threadIdHandle = threadIdHandle;
    motorsContext.rightMotorConfiguration.currentValues.refSpeed = 0;
    motorsContext.leftMotorConfiguration.currentValues.refSpeed = 0;
    motorsContext.leftMotorConfiguration.controllerParameters = create_pid(4000., 150., 30.);
    motorsContext.rightMotorConfiguration.controllerParameters = create_pid(4000., 150., 30.);

    struct FeedbackConfiguration leftFeedback = {
        .encoderAPort = LeftMotorEncoderA_GPIO_Port,
        .encoderAPin = LeftMotorEncoderA_Pin,
        .encoderBPort = LeftMotorEncoderB_GPIO_Port,
        .encoderBPin = LeftMotorEncoderB_Pin,
    };
    motorsContext.leftMotorConfiguration.feedbackConfiguration = leftFeedback;
    configure_feedback(&motorsContext.leftMotorConfiguration.feedbackConfiguration);

    struct FeedbackConfiguration rightFeedback = {
        .encoderAPort = RightMotorEncoderA_GPIO_Port,
        .encoderAPin = RightMotorEncoderA_Pin,
        .encoderBPort = RightMotorEncoderB_GPIO_Port,
        .encoderBPin = RightMotorEncoderB_Pin,
    };
    motorsContext.rightMotorConfiguration.feedbackConfiguration = rightFeedback;
    configure_feedback(&motorsContext.rightMotorConfiguration.feedbackConfiguration);

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

void work_motors_impl()
{
    if (osThreadFlagsWait(PROBING_TIMEOUT_CALLBACK, osFlagsWaitAll, 0) == osOK)
    {
        control();
    }

    static Message buffer;
    if (osMessageQueueGet(*motorsContext.messageQueueHandle, &buffer, 0, 0) == osOK)
    {
        LOG_INFO("New message to motors");
        message_dispatch_onMessageReceived(&buffer);
    }
    osThreadYield();
}

void control()
{
    double leftControlError =
        motorsContext.leftMotorConfiguration.currentValues.refSpeed -
            get_speed(&motorsContext.leftMotorConfiguration.feedbackConfiguration);
    double rightControlError =
        motorsContext.rightMotorConfiguration.currentValues.refSpeed -
            get_speed(&motorsContext.rightMotorConfiguration.feedbackConfiguration);

    int64_t uLeft = pid_evaluate(&motorsContext.leftMotorConfiguration.controllerParameters,
                                 leftControlError,
                                 SPEED_UPDATE_PERIOD);
    int64_t uRight = pid_evaluate(&motorsContext.rightMotorConfiguration.controllerParameters,
                                  rightControlError,
                                  SPEED_UPDATE_PERIOD);

    bool left = true;
    motor_process_update_u(&motorsContext.leftMotorConfiguration.controlConfiguration, uLeft, left);
    motor_process_update_u(&motorsContext.rightMotorConfiguration.controlConfiguration, uRight, !left);
}
