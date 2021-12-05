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

    osStatus_t messageQueueStatus = osMessageQueueGet(*logTaskContext.logsQueueHandle, &buffer, NULL, osWaitForever);
    if (messageQueueStatus != osOK)
    {
        return;
    }

    if (buffer.lineLength < MAX_LINE_LENGTH)
    {
        charactersAmountToBeSent = buffer.lineLength;
    }

    memcpy(logTaskContext.txBuffer, buffer.line, charactersAmountToBeSent);
    send(logTaskContext.txBuffer, charactersAmountToBeSent);
    free(buffer.line);

    osThreadFlagsWait(TRANSFER_COMPLETED_FLAG, osFlagsWaitAll, osWaitForever);
}

void sendToLogImpl(const char* characters)
{
    uint8_t len = strlen(characters);

    uint8_t* bytes = malloc(len + 1);
    strcpy((char *)bytes, characters);

    LogLine message = {
        .line = bytes,
        .lineLength = len
    };
    osMessageQueuePut(*logTaskContext.logsQueueHandle, &message, PRIORITY_0, NO_WAITING);
}
