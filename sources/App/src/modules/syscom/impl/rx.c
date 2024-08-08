/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.c
  * @brief          : Sources for RX handling of syscom module.
  ******************************************************************************
  */
#include <modules/syscom/impl/rx.h>

#include <main/module.h>
#include <modules/syscom/interface.h>
#include <modules/syscom/impl/msg_processor.h>
#include <modules/log/interface.h>
#include <msg/defs/Message.h>

#include <string.h>

void rx_start(struct module *this_mod, struct rx_context *context)
{
    struct comm_ops *rx_comm_ops = (this_mod->ops.communication_ops) + SYSCOM_SPI_COMM_INDEX;

    LOG_INFO("[syscom][rx] Waiting for message\n");
    memset(context->buffer, 0, FRAME_SIZE);

    int status = rx_comm_ops->read_non_blocking(context->buffer, FRAME_SIZE);
    if (status != 0)
    {
        LOG_INFO("[syscom][rx] ERROR when starting SPI reception using DMA\n");
    }
    LOG_INFO("[syscom][rx] SPI receiving\n");
}

void rx_work(struct module *this_mod, struct rx_context *context)
{
    struct syscom_data *data = (struct syscom_data *)module_get_data(this_mod);
    struct Message* msg = NULL;

    LOG_INFO("[syscom][rx] Received message\n");

    if (context->buffer[0] == HEADER_BYTE)
    {
        msg = processData(context->buffer);
    }
    
    if (msg != NULL)
    {
        osStatus_t status = osMessageQueuePut(*data->received_messages_queue_handle, msg, 0, 0);
        if (status != osOK)
        {
            LOG_INFO("[syscom][rx] Error occurred when putting message to queue\n");
        }
    }

    rx_start(this_mod, context);
}
