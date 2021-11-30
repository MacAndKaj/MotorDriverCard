/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface.h file.
  ******************************************************************************
  */

#include <MDC/log/interface.h>
#include <MDC/log/impl/log.h>
#include <MDC/log/impl/sender.h>

void configureLog(osMessageQueueId_t* messageQueueHandle, osThreadId_t* threadIdHandle)
{
    configureLogImpl(messageQueueHandle, threadIdHandle);
}

void workLog()
{
    workLogImpl();
}

//TODO: get rid of this function, it should be done by sub-cbk mechanism between sender and HalEventProxy
void onTransmitCompleted()
{
    onTransmitCompletedImpl();
}

void sendToLog(const char* characters)
{
    sendToLogImpl(characters);
}
