/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <MDC/motors/impl/pid.h>
#include <MDC/motors/impl/motor_process.h>
#include <MDC/motors/impl/feedback.h>
#include <MDC/motors/impl/defs.h>
#include <MDC/motors/impl/message_dispatch.h>
#include <MDC/log/interface.h>
#include <MDC/main/defs.h>
#include <msg/defs/Message.h>

#include <gpio.h>

#include <cmsis_os2.h>
#include <MDC/motors/impl/handlers/platform_set_motor_speed_req_handler.h>

/*

          ***           +-------------+      +-------------+
       + *    *   e(t)  |  Controller | u(t) |  Process    |  y(t)              
r(t)--->*      *------- |   (PID)     |----->|  (Motors)   |--------+--------->
         *    *         |             |      |             |        |
          ***           +-------------+      +-------------+        |
           ^ -                                                      |
           |                                                        |
           |                 +-------------+                        |
           |                 |             |                        |
           +-----------------|  Feedback   |<-----------------------+
                             |             |
                             +-------------+
*/

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

void periodicalCallbackImpl()
{
    feedback_handleFeedback(&motorsContext.rightMotorConfiguration.feedbackConfiguration, SPEED_UPDATE_PERIOD);
    feedback_handleFeedback(&motorsContext.leftMotorConfiguration.feedbackConfiguration, SPEED_UPDATE_PERIOD);
    osThreadFlagsSet(*motorsContext.threadIdHandle, PROBING_TIMEOUT_CALLBACK);
}

void onExtInterruptMotorsImpl(uint16_t GPIO_Pin)
{
    bool left = true, right = false;
    switch (GPIO_Pin)
    {
        case LeftMotorEncoderB_Pin:
            feedback_update(&motorsContext.rightMotorConfiguration.feedbackConfiguration, left);
            break;
        case RightMotorEncoderB_Pin:
            feedback_update(&motorsContext.rightMotorConfiguration.feedbackConfiguration, right);
            break;
        default:
            break;
    }
}

void control();

void configureMotorsImpl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    motorsContext.messageQueueHandle = messageQueueHandle;
    motorsContext.threadIdHandle = threadIdHandle;
    motorsContext.rightMotorConfiguration.currentValues.refSpeed = 0;
    motorsContext.leftMotorConfiguration.currentValues.refSpeed = 0;

    struct PIDParameters params = {
        .kP = 4000.,
        .kI = 150.,
        .kD = 30.,
    };
    motorsContext.leftMotorConfiguration.controllerParameters = params;
    motorsContext.rightMotorConfiguration.controllerParameters = params;

    struct FeedbackConfiguration leftFeedback = {
        .encoderAPort = LeftMotorEncoderA_GPIO_Port,
        .encoderAPin = LeftMotorEncoderA_Pin,
        .encoderBPort = LeftMotorEncoderB_GPIO_Port,
        .encoderBPin = LeftMotorEncoderB_Pin,
    };
    motorsContext.leftMotorConfiguration.feedbackConfiguration = leftFeedback;
    feedback_configure(&motorsContext.leftMotorConfiguration.feedbackConfiguration);

    struct FeedbackConfiguration rightFeedback = {
        .encoderAPort = RightMotorEncoderA_GPIO_Port,
        .encoderAPin = RightMotorEncoderA_Pin,
        .encoderBPort = RightMotorEncoderB_GPIO_Port,
        .encoderBPin = RightMotorEncoderB_Pin,
    };
    motorsContext.rightMotorConfiguration.feedbackConfiguration = rightFeedback;
    feedback_configure(&motorsContext.rightMotorConfiguration.feedbackConfiguration);

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

void workMotorsImpl()
{
    if (osThreadFlagsWait(PROBING_TIMEOUT_CALLBACK, osFlagsWaitAll, 0) == osOK)
    {
        control();
    }

    static Message buffer;
    if (osMessageQueueGet(*motorsContext.messageQueueHandle, &buffer, 0, 0) == osOK)
    {
        logInfo("New message to motors");
        message_dispatch_onMessageReceived(&buffer);
    }
    osThreadYield();
}

void control()
{
    double leftControlError =
        motorsContext.leftMotorConfiguration.currentValues.refSpeed -
        feedback_getSpeed(&motorsContext.leftMotorConfiguration.feedbackConfiguration);
    double rightControlError =
        motorsContext.rightMotorConfiguration.currentValues.refSpeed -
        feedback_getSpeed(&motorsContext.rightMotorConfiguration.feedbackConfiguration);

    int64_t uLeft = pid_evaluate(&motorsContext.leftMotorConfiguration.controllerParameters,
                                 leftControlError,
                                 SPEED_UPDATE_PERIOD);
    int64_t uRight = pid_evaluate(&motorsContext.rightMotorConfiguration.controllerParameters,
                                  rightControlError,
                                  SPEED_UPDATE_PERIOD);

    bool left = true;
    motor_process_updateU(&motorsContext.leftMotorConfiguration.controlConfiguration, uLeft, left);
    motor_process_updateU(&motorsContext.rightMotorConfiguration.controlConfiguration, uRight, !left);
}
