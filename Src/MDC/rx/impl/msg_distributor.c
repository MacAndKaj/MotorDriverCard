/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : msg_distributor.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <MDC/rx/impl/msg_distributor.h>
#include "MDC/log/interface.h"

struct
{
    osMessageQueueId_t* messageQueueHandle;
} msgDistributorContext;

void configureMsgDistributor(osMessageQueueId_t* messageQueueHandle)
{
    msgDistributorContext.messageQueueHandle = messageQueueHandle;
}

void forwardMessage(const Message* msg)
{
    osStatus_t status = osMessageQueuePut(*msgDistributorContext.messageQueueHandle, msg, 0, 0);
    if (status != osOK)
    {
       logInfo("Error occurred when putting message to queue");
    }
}
