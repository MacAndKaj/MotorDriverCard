/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : msg_distributor.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include "tasks/rx/impl/msg_distributor.h"
#include "log/interface.h"

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
        LOG_INFO("Error occurred when putting message to queue\n");
    }
}
