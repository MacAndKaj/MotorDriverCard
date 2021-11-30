/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : This file contains interface of log task and its functionalities
  ******************************************************************************
  */
#ifndef MOTORDRIVERCARD_LOG_INTERFACE_H
#define MOTORDRIVERCARD_LOG_INTERFACE_H

#include <cmsis_os2.h>

#include <stdint.h>

#define LOG(line) sendToLog(line"\r\n")

/// Logging function - can be used from other threads.
/// \param characters
void sendToLog(const char* characters);

//TODO: move to log impl, change to function returning size of LogLine
typedef struct
{
    uint8_t* line;
    uint8_t lineLength;
} LogLine;

/// Message to configure LogTask.
/// \param messageQueueHandle: handle to messageQueue used to queue new logs to be sent
/// \param threadIdHandle: threadId of LogTask
void configureLog(osMessageQueueId_t* messageQueueHandle, osThreadId_t* threadIdHandle);

/// Main LogTask function.
void workLog();

/// Function used in callbacks when transmission is done.\n
/// NOTE: DEPRECATED - will be removed when subscribing for HAL events is ready
void onTransmitCompleted();

#endif //MOTORDRIVERCARD_LOG_INTERFACE_H
