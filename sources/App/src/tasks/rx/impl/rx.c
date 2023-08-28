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
#include "msg/defs/Frame.h"
#include "tasks/rx/impl/rx.h"
#include "tasks/rx/impl/msg_processor.h"
#include "tasks/rx/impl/msg_distributor.h"

#include "usart.h"

#include <FreeRTOS.h>

#include <string.h>

struct
{
    osThreadId_t* receiverThreadIdHandle;
    uint8_t rxBuffer[FRAME_SIZE];
} rxContext;

void startReception()
{
    LOG_INFO("Waiting for message\n");
    memset(rxContext.rxBuffer, 0, FRAME_SIZE);
    HAL_StatusTypeDef status = HAL_UART_Receive_DMA(&huart3, rxContext.rxBuffer, sizeof(Frame));

    if (status != HAL_OK)
    {
        LOG_INFO("ERROR when starting UART reception using DMA for UART3\n");
    }
}

void configureRxImpl(osThreadId_t* receiverThreadIdHandle, osMessageQueueId_t* messageQueueHandle)
{
    rxContext.receiverThreadIdHandle = receiverThreadIdHandle;

    configureMsgDistributor(messageQueueHandle);
    
    startReception();
}

void workRxImpl()
{
    osThreadFlagsWait(DATA_RECEIVED_THREAD_FLAG, osFlagsWaitAny, osWaitForever);

    LOG_INFO("[RX]Received message\n");
    struct Message* msg = processData(rxContext.rxBuffer);
    if (msg != NULL)
    {
        forwardMessage(msg);
    }

    startReception();
}

void onReceptionCompletedImpl()
{
    osThreadFlagsSet(*rxContext.receiverThreadIdHandle, DATA_RECEIVED_THREAD_FLAG);
}
