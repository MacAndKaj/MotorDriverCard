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

uint32_t getLogMessageSize()
{
    return getLogMessageSizeImpl();
}

void configureLog(osMessageQueueId_t* messageQueueHandle, osThreadId_t* threadIdHandle)
{
    configureLogImpl(messageQueueHandle, threadIdHandle);
}

void workLog()
{
    workLogImpl();
}

//TODO: get rid of this function, it should be done by sub-clbk mechanism between sender and HalEventProxy
void onTransmitCompleted()
{
    onTransmitCompletedImpl();
}


int _write(int file, char *ptr, int len)
{
    (void*)file;
    if (len == 0)
    {
        return len;
    }

    sendToLogImpl(ptr, len);

    return 0;
}
