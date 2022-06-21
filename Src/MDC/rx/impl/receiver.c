/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : receiver.c
  * @brief          : <brief>
  ******************************************************************************
  */

#include <log/interface.h>

#include <MDC/rx/impl/receiver.h>

#include <usart.h>

struct
{
    osThreadId_t* threadIdHandle;
} receiverContext;

void configureReceiver(osThreadId_t* rxThreadId)
{
    receiverContext.threadIdHandle = rxThreadId;
}

void startReception(uint8_t* dest, uint16_t N)
{
    HAL_StatusTypeDef status = HAL_UART_Receive_DMA(&huart2, dest, N);

    if (status != HAL_OK)
    {
        LOG_INFO("ERROR when receiving from UART2");
    }
}

void onReceptionCompletedImpl()
{
    osThreadFlagsSet(*receiverContext.threadIdHandle, DATA_RECEIVED_THREAD_FLAG);
}
