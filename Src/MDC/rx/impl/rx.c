/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.c
  * @brief          : Main RxTask file - entry point of task.
  ******************************************************************************
  */

#include <MDC/rx/impl/rx.h>

#include <MDC/log/interface.h>
#include <MDC/rx/impl/receiver.h>
#include <MDC/rx/impl/msg_processor.h>
#include <MDC/rx/impl/msg_distributor.h>

#include <msg/consts.h>

#include <malloc.h>

struct
{
    uint8_t* data;
} rxBuffer;

void clearBuffer(uint16_t nextReadSize)
{
    if (rxBuffer.data == NULL) return;

    free(rxBuffer.data);
    rxBuffer.data = (uint8_t *) malloc(nextReadSize * sizeof(uint8_t));
}

void configureRxImpl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    configureMsgProcessor();
    configureMsgDistributor(messageQueueHandle);
    configureReceiver(threadIdHandle);

    rxBuffer.data = (uint8_t *) malloc(getNextMessageSize() * sizeof(uint8_t));
    startReception(rxBuffer.data, getNextMessageSize());
}

void workRxImpl()
{
    osThreadFlagsWait(DATA_RECEIVED_THREAD_FLAG, osFlagsWaitAny, osWaitForever);

    switch (getNextDataType())
    {
        case FrameCtrlData:
        {
            logInfo("Waiting for new message to be received");
            processFrameCtrlData(rxBuffer.data);
            break;
        }
        case UserData:
        {
            logInfo("__FUNCTION__|Received message");
            Message* msg = processUserData(rxBuffer.data);
            forwardMessage(msg);
            if (msg != NULL)
            {
                free(msg);
            }
            break;
        }
        default:
        {
            logInfo("Incorrect data type");
        }
    }

    clearBuffer(getNextMessageSize());
    startReception(rxBuffer.data, getNextMessageSize());
}
