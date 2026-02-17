/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.c
  * @brief          : Sources for RX handling of syscom module.
  ******************************************************************************
  */
#include <stdbool.h>
#include <modules/syscom/impl/rx.h>

#include <main/defs.h>
#include <main/module.h>
#include <modules/syscom/interface.h>
#include <modules/syscom/impl/msg_processor.h>
#include <modules/log/interface.h>
#include <msg/defs/Message.h>

#include <string.h>


void rx_start(struct module *this_mod, struct rx_context *context)
{
    (void)this_mod;
    memset(context->buffer, 0, FRAME_SIZE);
    LOG_INFO("[syscom][rx] SPI receiving\n");
}

bool check_crc(struct comm_ops* ops, uint8_t* buffer)
{
    uint8_t calculated_crc = (ops->calculate_crc(buffer, FRAME_SIZE-1) & 0xFF);
    uint8_t received_crc = buffer[FRAME_SIZE - 1];
    if (calculated_crc != received_crc)
    {
        LOG_INFO_ARGS("[syscom][rx] CRC check failed exp: %02x, rec: %02x\n", calculated_crc, received_crc);
        return false;
    }
    return true;
}

void rx_work(struct module *this_mod, struct rx_context *context)
{
    struct syscom_data *data = module_get_data(this_mod);

    if (!check_crc(this_mod->ops.communication_ops, context->buffer))
    {
        return;
    }
    const Message* msg = process_data(context->buffer);
    if (msg != NULL)
    {
        LOG_INFO_ARGS("Received msg: id: %d\n", msg->messageId);
        struct message_subscription *subscription = data->subs;
        for (int i = 0; i < data->subs_len; i++)
        {
            if (subscription->msg_id == msg->messageId)
            {
                if (osMessageQueuePut(*subscription->subscription_queue, msg, 0, 0) != osOK)
                {
                    LOG_INFO("[syscom][rx] Error occurred when putting message to queue\n");
                }
            }
            ++subscription;
        }
    }
}
