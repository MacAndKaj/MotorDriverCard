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
    free(buffer.line);

    osThreadFlagsWait(TRANSFER_COMPLETED_FLAG, osFlagsWaitAll, osWaitForever);
}

void logImpl(const char* severityStr, const char* characters, ...)
{
    char logFormatBuffer[MAX_LINE_LENGTH];

    size_t severityStrLen = strlen(severityStr);
    memcpy(logFormatBuffer, severityStr, severityStrLen);

    va_list args;
    va_start(args, characters);
    vsnprintf(logFormatBuffer + severityStrLen, (MAX_LINE_LENGTH-severityStrLen), characters, args);
    va_end(args);

    uint8_t logLength = strlen(logFormatBuffer);
    logFormatBuffer[logLength]='\n';
    logLength = logLength + 1;

    uint8_t* bytes = malloc(logLength);
    memcpy(bytes, logFormatBuffer, logLength);
    LogLine message = {
        .line = bytes,
        .lineLength = logLength
    };

    osMessageQueuePut(*logTaskContext.logsQueueHandle, &message, PRIORITY_0, 0);
}
