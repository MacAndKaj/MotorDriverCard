/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.c
  * @brief          : Sources for RX handling of syscom module.
  ******************************************************************************
  */
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

void rx_work(struct module *this_mod, struct rx_context *context)
{
    struct syscom_data *data = module_get_data(this_mod);

    // if (!check_crc(context->buffer))
    // {
    //     // handle crc error
    //     LOG_INFO("[syscom][rx] CRC check failed\n");
    //     return;
    // }
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
