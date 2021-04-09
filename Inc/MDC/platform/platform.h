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

extern double speedUpdateTime;

struct CommunicationContext;

struct PlatformContext;
typedef struct PlatformContext PlatformContext;

PlatformContext* createPlatformContext();

void initPlatform(PlatformContext* platformContext);
void workPlatform(PlatformContext* platformContext);

#endif //MOTORDRIVER_PLATFORM_H
