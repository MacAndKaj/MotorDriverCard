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
#include <MDC/motors/impl/handlers/platform_set_motor_speed_req_handler.h>
#include <MDC/main/defs.h>
#include <msg/defs/Message.h>
#include <msg/message_ids.h>

#include "gpio.h"
#include "cmsis_os2.h"
#include "MDC/log/interface.h"

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


void onMessageReceived(const Message* message);
void control();

void configureMotorsImpl()
{
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

    struct FeedbackConfiguration rightFeedback = {
        .encoderAPort = RightMotorEncoderA_GPIO_Port,
        .encoderAPin = RightMotorEncoderA_Pin,
        .encoderBPort = RightMotorEncoderB_GPIO_Port,
        .encoderBPin = RightMotorEncoderB_Pin,
    };
    motorsContext.rightMotorConfiguration.feedbackConfiguration = rightFeedback;

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
        onMessageReceived(&buffer);
    }
}

void onMessageReceived(const Message* msg)
{
    logInfo("[motors]Message with id=%d received.\r\n", msg->messageId);
    switch (msg->messageId)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            handlePlatformSetMotorSpeedReq(&msg->msg.platformSetMotorSpeedReq);
            break;
        default:
            logInfo("Unknown messageId, ignoring!\r\n");
    }
}

void periodicalCallbackImpl()
{
    handleFeedback(&motorsContext.rightMotorConfiguration.feedbackConfiguration, SPEED_UPDATE_PERIOD);
    handleFeedback(&motorsContext.leftMotorConfiguration.feedbackConfiguration, SPEED_UPDATE_PERIOD);
    osThreadFlagsSet(*motorsContext.threadIdHandle, PROBING_TIMEOUT_CALLBACK);
}

void control()
{
    double leftControlError = 
        motorsContext.leftMotorConfiguration.currentValues.refSpeed - 
        getSpeed(&motorsContext.leftMotorConfiguration.feedbackConfiguration);
    double rightControlError = 
        motorsContext.rightMotorConfiguration.currentValues.refSpeed - 
        getSpeed(&motorsContext.rightMotorConfiguration.feedbackConfiguration);

    int64_t uLeft = evaluate(&motorsContext.leftMotorConfiguration.controllerParameters, 
            leftControlError, 
            SPEED_UPDATE_PERIOD);
    int64_t uRight = evaluate(&motorsContext.rightMotorConfiguration.controllerParameters, 
            rightControlError, 
            SPEED_UPDATE_PERIOD);
    
    bool left = true;
    updateU(&motorsContext.leftMotorConfiguration.controlConfiguration, uLeft, left);
    updateU(&motorsContext.rightMotorConfiguration.controlConfiguration, uRight, !left);
}
