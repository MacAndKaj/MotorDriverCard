/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : platform.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <MDC/platform/platform.h>
#include <MDC/com/interface/message_ids.h>
#include <MDC/com/interface/defs/Message.h>
#include <MDC/com/interface/defs/PlatformSetMotorSpeed.h>

#include <malloc.h>
#include <MDC/platform/pid.h>
#include <MDC/platform/motor_info.h>
#include <MDC/platform/motor_control.h>
#include <MDC/main/defs.h>
#include <stdio.h>

double speedUpdateTime = 1./SPEED_UPDATE_FREQ;

typedef struct MotorProperties
{
    PID pidController;
    double controlError;
    double speed;
} MotorProperties;

typedef struct PlatformContext
{
    MotorProperties leftMotorProperties;
    MotorProperties rightMotorProperties;
} PlatformContext;

PlatformContext* platformContext;

/// Function initializing Motor Driver configuration.
void init_MotorDriver();

/// Creates default PlatformContext object.
/// \return Pointer to PlatformContext
PlatformContext* createPlatformContext();

/* PUBLIC DEFINITIONS BEGIN */


void initPlatform()
{
    platformContext = createPlatformContext();

    init_MotorDriver();
}

void workPlatform()
{
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
}
/* PUBLIC DEFINITIONS END */


/* PRIVATE DEFINITIONS BEGIN */
PlatformContext* createPlatformContext()
{
    PlatformContext* temp = (struct PlatformContext*)malloc(sizeof(struct PlatformContext));
    PID temporaryPID = {
        .kP = 4000.,
        .kI = 150.,
        .kD = 30.
    };
    platformContext->rightMotorProperties.pidController = temporaryPID;
    platformContext->leftMotorProperties.pidController = temporaryPID;

    platformContext->rightMotorProperties.controlError = 0;
    platformContext->leftMotorProperties.controlError = 0;

    platformContext->rightMotorProperties.speed = 0;
    platformContext->leftMotorProperties.speed = 0;

    return platformContext;
}

double transformSpeed(int8_t speedInt, uint8_t speedFl)
{
    if (speedInt < 0)
    {
        return speedInt - (speedFl * 0.01);
    }
    return speedInt + (speedFl * 0.01);
}

void init_MotorDriver()
{
    initializeLeftMotor();
    initializeRightMotor();
    setLeftDirection(FORWARD);
    setRightDirection(FORWARD);
}

void workPlatformPeriodical()
{
    updateSpeed(&rightMotorHandle, speedUpdateTime);
    updateSpeed(&leftMotorHandle, speedUpdateTime);
    enableSpeedUpdateFlag(&rightMotorHandle);
    enableSpeedUpdateFlag(&leftMotorHandle);
}

void rightMotorEncoderCallback()
{
    updateLeftMotorParameters();
}

void leftMotorEncoderCallback()
{
    updateRightMotorParameters();
}


void toggleSpeed(PlatformSetMotorSpeedReq* req)
{
    if (req->motor == 0)
    {
        platformContext->leftMotorProperties.speed = transformSpeed(req->speedI, req->speedF);
        printf("New left speed: %f\r\n", platformContext->leftMotorProperties.speed);
    }
    else
    {
        platformContext->rightMotorProperties.speed = transformSpeed(req->speedI, req->speedF);
        printf("New right speed: %f\r\n", platformContext->rightMotorProperties.speed);
    }
}

void onMessageReceivedPlatform(struct Message* message)
{
    printf("[platform]Message with id=%d received.\r\n", message->messageId);
    switch (message->messageId)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            toggleSpeed(&message->msg.platformSetMotorSpeedReq);
            break;
        default:
            printf("Unknown messageId, ignoring!\r\n");
    }
}



/* PRIVATE DEFINITIONS END */