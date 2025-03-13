/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : tx.c
  * @brief          : Sources for TX handling of syscom module.
  ******************************************************************************
  */
#include <modules/syscom/impl/tx.h>

#include <main/module.h>
#include <modules/syscom/interface.h>
#include <modules/syscom/impl/msg_processor.h>
#include <modules/log/interface.h>
#include <msg/defs/Message.h>

#include <string.h>

void tx_start(struct module * mod, struct tx_context *context)
{
    (void)mod;
    (void)context;
    LOG_INFO("[syscom][tx] Initialized\n");
}

void tx_work(struct module *this_mod, struct tx_context *context)
{
    struct syscom_data *data = (struct syscom_data *)module_get_data(this_mod);
    struct comm_ops *syscom_ops = this_mod->ops.communication_ops;
    
    Message message_buffer;
    memset(&message_buffer, 0, sizeof(Message));
    
    LOG_INFO("[syscom][tx] Sending message\n");
    
    if (osMessageQueueGet(*data->transferred_messages_queue_handle, &message_buffer, 0, 0) == osOK)
    {
        process_message(&message_buffer, context->buffer);

        int result = syscom_ops->write_non_blocking(context->buffer, FRAME_SIZE);
        if (result != 0)
        {
            LOG_INFO_ARGS("[syscom][tx] Error when writing: %d\n", result);
        }
        data->comm_master_trigger_up();
        if (osTimerStart(*data->syscom_timer_handle, 100) != osOK)
        {
            LOG_INFO("[syscom][tx] Error when starting timer\n");
            data->comm_master_trigger_down();
        }
    }
    else
    {
        LOG_INFO("[syscom][tx] Error when getting message\n");
    }
}
