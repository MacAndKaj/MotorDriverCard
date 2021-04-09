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
#include <MDC/com/com.h>
#include <MDC/com/interface/defs/PlatformSetMotorSpeed.h>

#include <malloc.h>
#include <MDC/platform/pid.h>
#include <MDC/platform/motor_info.h>
#include <MDC/platform/motor_control.h>
#include <MDC/main/defs.h>

double speedUpdateTime = 1./SPEED_UPDATE_FREQ;

/// Function initializing Motor Driver configuration.
/// \return [int]: 0 if not error, 1 - otherwise
int init_MotorDriver();

typedef struct MotorProperties
{
    PID pidController;
    double controlError;
    double speed;
} MotorProperties;

struct PlatformContext
{
    MotorProperties leftMotorProperties;
    MotorProperties rightMotorProperties;
};

/* PUBLIC DEFINITIONS BEGIN */

PlatformContext* createPlatformContext()
{
    PlatformContext* platformContext = (struct PlatformContext*)malloc(sizeof(struct PlatformContext));
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

void initPlatform(PlatformContext* platformContext)
{
    (void*)platformContext;
}

void workPlatform(PlatformContext* platformContext)
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

double transformSpeed(int8_t speedInt, uint8_t speedFl)
{
    if (speedInt < 0)
    {
        return speedInt - (speedFl * 0.01);
    }
    return speedInt + (speedFl * 0.01);
}

int init_MotorDriver()
{
    initializeLeftMotor();
    initializeRightMotor();
    setLeftDirection(FORWARD);
    setRightDirection(FORWARD);
    return 0;
}



/* PRIVATE DEFINITIONS END */