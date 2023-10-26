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
#include "spi.h"

#include <FreeRTOS.h>

#include <string.h>

struct
{
    osThreadId_t* receiverThreadIdHandle;
    uint8_t rxBuffer[FRAME_SIZE];
    uint8_t syscomRxBuffer[FRAME_SIZE];
} rxContext;

void startReception()
{
    LOG_INFO("Waiting for message\n");
    memset(rxContext.rxBuffer, 0, FRAME_SIZE);
    memset(rxContext.syscomRxBuffer, 0, FRAME_SIZE);

    if (HAL_UART_GetState(&huart3) == 32)
    {
        HAL_StatusTypeDef status = HAL_UART_Receive_DMA(&huart3, rxContext.rxBuffer, sizeof(Frame));
        if (status != HAL_OK)
        {
            LOG_INFO("ERROR when starting UART reception using DMA\n");
        }
         LOG_INFO("UART receiving\n");
    }

    if (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_READY)
    {
        HAL_StatusTypeDef status = HAL_SPI_Receive_DMA(&hspi2, rxContext.syscomRxBuffer, FRAME_SIZE);
        if (status != HAL_OK)
        {
            LOG_INFO("ERROR when starting SPI reception using DMA\n");
        }
        LOG_INFO("SPI receiving\n");
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

    struct Message* msg;
    if (rxContext.rxBuffer[0] == HEADER_BYTE)
    {
        msg = processData(rxContext.rxBuffer);
    }
    else
    {
        msg = processData(rxContext.syscomRxBuffer);
    }
    
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
