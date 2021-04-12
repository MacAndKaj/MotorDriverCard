/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : platform.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_PLATFORM_H
#define MOTORDRIVER_PLATFORM_H

#define SPEED_UPDATE_FREQ 100.0

/* FORWARD DECLARATION BEGIN*/
extern double speedUpdateTime;

struct Message;
/* FORWARD DECLARATION END*/


/* FUNCTIONS DECLARATION BEGIN*/
void initPlatform();
void workPlatform();
void workPlatformPeriodical();

void leftMotorEncoderCallback();
void rightMotorEncoderCallback();

void onMessageReceivedPlatform(struct Message* message);
/* FUNCTIONS DECLARATION END*/

#endif //MOTORDRIVER_PLATFORM_H
