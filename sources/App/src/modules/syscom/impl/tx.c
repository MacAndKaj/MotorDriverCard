/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : tx.c
  * @brief          : Sources for TX handling of syscom module.
  ******************************************************************************
  */
#include <modules/syscom/impl/tx.h>

#include <main/defs.h>
#include <main/module.h>
#include <modules/syscom/interface.h>
#include <modules/syscom/impl/msg_processor.h>
#include <modules/log/interface.h>
#include <msg/defs/Message.h>

#include <string.h>

#include "msg/message_ids.h"

#define SPI_MASTER_TRIGGER_TICKS 50 // 50 ticks = 50ms,

void tx_start(struct module * mod, struct tx_context *context)
{
    (void)mod;
    context->status_to_send.messageId = PLATFORM_STATUS_MSG_ID;
    LOG_INFO("[syscom][tx] Initialized\n");
}

void tx_work(struct module *this_mod, struct tx_context *context)
{
    struct syscom_data *data = module_get_data(this_mod);

    InternalMessage message_buffer = {0};
    // tutaj trzeba przemyslec jak aktualizowac status do wyslania bo enkodery aktualizuja znacznie czesciej
    // wiec trzeba jakos wspolnie odswiezac to - moze jakas wspolna funkcja do akutalizowania - mutex(grozi deadlockiem)
    if (osMessageQueueGet(*data->transferred_messages_queue_handle, &message_buffer, 0, 0) == osOK)
    {
        LOG_INFO("[syscom][tx] Received message to process\n");
        process_message(&message_buffer, &context->status_to_send.msg.platform_status);
    }
    prepare_frame(&context->status_to_send, context->buffer);
}

void tx_callback(struct module *this_mod, struct tx_context *context)
{
    (void)this_mod;
    (void)context;
}

