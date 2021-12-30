/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motors.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <MDC/platform/platform.h>
#include "msg/message_ids.h"
#include "msg/defs/Message.h"
#include "msg/defs/PlatformSetMotorSpeed.h"

#include <malloc.h>
#include <MDC/platform/pid.h>
#include <MDC/platform/motor_info.h>
#include <MDC/platform/motor_control.h>
#include "MDC/main/defs.h"
#include <stdio.h>
#include "MDC/log/interface.h"

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


void initPlatform(void)
{
    platformContext = createPlatformContext();

    init_MotorDriver();
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
    temp->rightMotorProperties.pidController = temporaryPID;
    temp->leftMotorProperties.pidController = temporaryPID;

    temp->rightMotorProperties.controlError = 0;
    temp->leftMotorProperties.controlError = 0;

    temp->rightMotorProperties.speed = 0;
    temp->leftMotorProperties.speed = 0;

    return temp;
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
    if (req->lMotor == 1)
    {
        platformContext->leftMotorProperties.speed = transformSpeed(req->lSpeedI, req->lSpeedF);
        logInfo("New left speed: %f\r\n", platformContext->leftMotorProperties.speed);
    }

    if (req->rMotor == 1)
    {
        platformContext->rightMotorProperties.speed = transformSpeed(req->rSpeedI, req->rSpeedF);
        logInfo("New right speed: %f\r\n", platformContext->rightMotorProperties.speed);
    }
}

void onMessageReceivedPlatform(struct Message* message)
{
    logInfo("[motors]Message with id=%d received.\r\n", message->messageId);
    switch (message->messageId)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            toggleSpeed(&message->msg.platformSetMotorSpeedReq);
            break;
        default:
            logInfo("Unknown messageId, ignoring!\r\n");
    }
}



/* PRIVATE DEFINITIONS END */