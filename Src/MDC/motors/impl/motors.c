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
#include <MDC/main/defs.h>
#include <msg/defs/Message.h>

#include "gpio.h"
#include "cmsis_os2.h"
#include "MDC/log/interface.h"

typedef struct
{
    struct FeedbackConfiguration feedbackConfiguration;
    struct ControlConfiguration controlConfiguration;
    struct PIDParameters controllerParameters;
} MotorConfiguration;

static struct
{
    MotorConfiguration leftMotorConfiguration;
    MotorConfiguration rightMotorConfiguration;
    osMessageQueueId_t* messageQueueHandle;
} motorsContext;


double transformSpeed(int8_t speedInt, uint8_t speedFl);
void onMessageReceived(const Message* message);


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
    };
    motorsContext.leftMotorConfiguration.controlConfiguration = leftMotorConfig;

    struct OutputConfiguration rightMotorConfig = {
            .stopThreshold = STOP_THRESHOLD,
            .pwmPeriod = PWM_PERIOD,
            .motorControl1Port = RightMotorIn1_GPIO_Port,
            .motorControl1Pin = RightMotorIn1_Pin,
            .motorControl2Port = RightMotorIn2_GPIO_Port,
            .motorControl2Pin = RightMotorIn2_Pin,
    };
    motorsContext.rightMotorConfiguration.controlConfiguration = rightMotorConfig;
}

void workMotorsImpl()
{
    //triggered only by events: update from encoders, new message in queue
    // 1. check updates from encoders
    // 1.1 handle update from encoders
    // 2. check new messages
    // 2.1 handle new messages

    MotorProperties* mP;
    if (isSpeedUpdateFlagSet(&leftMotorHandle))
    {
        mP = &platformContext->leftMotorProperties;
        disableSpeedUpdateFlag(&leftMotorHandle);

        mP->controlError = mP->speed - getSpeed(&leftMotorHandle);

        setLeftPwm((int64_t)evaluate(&mP->pidController, mP->controlError, speedUpdateTime));
    }

    if (isSpeedUpdateFlagSet(&rightMotorHandle))
    {
        mP = &platformContext->rightMotorProperties;
        disableSpeedUpdateFlag(&rightMotorHandle);

        mP->controlError = mP->speed - getSpeed(&rightMotorHandle);

        setRightPwm((int64_t)evaluate(&mP->pidController, mP->controlError, speedUpdateTime));
    }

    static Message buffer;
    if (osMessageQueueGet(*motorsContext.messageQueueHandle, &buffer, 0, 0) == osOK)
    {
        logInfo("New message to motors");
        onMessageReceived(&buffer);
    }
}

double transformSpeed(int8_t speedInt, uint8_t speedFl)
{
    if (speedInt < 0)
    {
        return speedInt - (speedFl * 0.01);
    }
    return speedInt + (speedFl * 0.01);
}

void onMessageReceived(const Message* msg)
{

}