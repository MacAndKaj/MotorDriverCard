/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface.h file.
  ******************************************************************************
  */
#include <MDC/log/impl/log.h>

#include <MDC/log/impl/def.h>
#include <MDC/log/impl/sender.h>

#include <memory.h>
#include <stddef.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <MDC/main/defs.h>
#include <main.h>

#define PRIORITY_0 0
#define NO_WAITING 0

struct {
    osMessageQueueId_t* logsQueueHandle;
    uint8_t txBuffer[MAX_LINE_LENGTH];
} logTaskContext;

uint32_t getLogMessageSizeImpl()
{
    return sizeof(LogLine);
}

void configureLogImpl(osMessageQueueId_t* messageQueueHandle, osThreadId_t* threadIdHandle)
{
    logTaskContext.logsQueueHandle = messageQueueHandle;

    memset(logTaskContext.txBuffer, (uint8_t) '?', MAX_LINE_LENGTH);

    configureSender(threadIdHandle);
}

void workLogImpl()
{
    static LogLine buffer = {};
    uint8_t charactersAmountToBeSent = MAX_LINE_LENGTH;

    osStatus_t messageQueueStatus = osMessageQueueGet(*logTaskContext.logsQueueHandle, &buffer, PRIORITY_0, osWaitForever);
    if (messageQueueStatus != osOK)
    {
        return;
    }

    if (buffer.lineLength <= MAX_LINE_LENGTH)
    {
        charactersAmountToBeSent = buffer.lineLength;
    }

    memcpy(logTaskContext.txBuffer, buffer.line, charactersAmountToBeSent);
    send(logTaskContext.txBuffer, charactersAmountToBeSent);

    osThreadFlagsWait(TRANSFER_COMPLETED_FLAG, osFlagsWaitAll, osWaitForever);
    free(buffer.line);
}

void logImpl(const char* severityStr, const char* characters)
{
    // TODO: here is problematic part when va_args used, need to be debugged
    size_t severityStrLen = strlen(severityStr);
    size_t charactersLen = strlen(characters);
    size_t limit = severityStrLen + charactersLen < MAX_LINE_LENGTH ? severityStrLen + charactersLen : MAX_LINE_LENGTH;

    uint8_t* bytes = malloc(limit + 1);
    memcpy(bytes, severityStr, severityStrLen);
    memcpy(bytes+severityStrLen, characters, charactersLen);
    bytes[limit] = '\n';
    LogLine message = {
        .line = bytes,
        .lineLength = limit + 1
    };

    if (osMessageQueuePut(*logTaskContext.logsQueueHandle, &message, PRIORITY_0, 0) != osOK)
    {
        Error_Handler();
    }
}
