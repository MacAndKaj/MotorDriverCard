/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.c
  * @brief          : Main RxTask file - entry point of task.
  ******************************************************************************
  */

#include "log/interface.h"
#include "main/defs.h"
#include "msg/consts.h"
#include "tasks/rx/impl/rx.h"
#include "tasks/rx/impl/receiver.h"
#include "tasks/rx/impl/msg_processor.h"
#include "tasks/rx/impl/msg_distributor.h"

#include <FreeRTOS.h>

struct
{
    uint8_t* data;
} rxBuffer;

void clearBuffer(uint16_t nextReadSize)
{
    if (rxBuffer.data == NULL) return;

    vPortFree(rxBuffer.data);
    rxBuffer.data = (uint8_t *) pvPortMalloc(nextReadSize * sizeof(uint8_t));
}

void configureRxImpl(osThreadId_t* threadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    configureMsgProcessor();
    configureMsgDistributor(messageQueueHandle);
    configureReceiver(threadIdHandle);

    rxBuffer.data = (uint8_t *) pvPortMalloc(getNextMessageSize() * sizeof(uint8_t));
    startReception(rxBuffer.data, getNextMessageSize());
}

void workRxImpl()
{
    osThreadFlagsWait(DATA_RECEIVED_THREAD_FLAG, osFlagsWaitAny, osWaitForever);

    switch (getNextDataType())
    {
        case FrameCtrlData:
        {
            LOG_INFO("workRxImpl: Waiting for new message to be received\n");
            processFrameCtrlData(rxBuffer.data);
            break;
        }
        case UserData:
        {
            LOG_INFO("workRxImpl: Received message\n");
            Message* msg = processUserData(rxBuffer.data);
            forwardMessage(msg);
            if (msg != NULL)
            {
                vPortFree(msg);
            }
            break;
        }
        default:
        {
            LOG_INFO("workRxImpl: Incorrect data type\n");
        }
    }

    clearBuffer(getNextMessageSize());
    startReception(rxBuffer.data, getNextMessageSize());
}
