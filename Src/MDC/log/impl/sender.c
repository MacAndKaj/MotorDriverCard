/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : sender.c
  * @brief          : Sources for sender.h file.
  ******************************************************************************
  */

#include <MDC/log/impl/sender.h>

#include <usart.h>
#include <MDC/log/impl/def.h>

struct {
    osThreadId_t* handle;
} senderContext;

void configureSender(osThreadId_t* threadIdHandle)
{
    senderContext.handle = threadIdHandle;
}

int send(uint8_t* bytes, uint8_t count)
{
    return HAL_UART_Transmit_DMA(&huart4, bytes, count) == HAL_OK;
}

void onTransmitCompletedImpl()
{
    osThreadFlagsSet(*senderContext.handle, TRANSFER_COMPLETED_FLAG);
}