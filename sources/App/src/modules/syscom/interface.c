/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Source file for interface of Syscom module.
  *                   This file contains interface definitions for using Syscom module.
  ******************************************************************************
  */

#include <modules/syscom/interface.h>

#include <main/defs.h>
#include <main/module.h>
#include <modules/syscom/impl/rx.h>
#include <modules/syscom/impl/tx.h>

struct syscom_internal_data
{
    struct rx_context rx_ctx;
    struct tx_context tx_ctx;
};

static struct syscom_internal_data internal_data;

void syscom_module_work(struct module *this_mod)
{
    osThreadFlagsWait(DATA_RECEIVED_THREAD_FLAG | DATA_TX_BUFFERED_THREAD_FLAG, 
                      osFlagsWaitAny | osFlagsNoClear,
                      osWaitForever);
    
    if (osThreadFlagsGet() && DATA_RECEIVED_THREAD_FLAG)
    {
        rx_work(this_mod, &internal_data.rx_ctx);
        osThreadFlagsClear(DATA_RECEIVED_THREAD_FLAG);
    }

    if (osThreadFlagsGet() && DATA_TX_BUFFERED_THREAD_FLAG)
    {
        tx_work(this_mod, &internal_data.tx_ctx);
        osThreadFlagsClear(DATA_TX_BUFFERED_THREAD_FLAG);
    }
}

void syscom_module_init(struct module *syscom_module)
{
    struct syscom_data *data = (struct syscom_data *)module_get_data(syscom_module);
    data->internal_data_handle = &internal_data;
    
    syscom_module->ops.work_ops = syscom_module_work;

    rx_start(syscom_module, &internal_data.rx_ctx);
    tx_start(syscom_module, &internal_data.tx_ctx);
}

void syscom_module_timer_callback(struct module *this_module)
{
    struct syscom_data *data = (struct syscom_data *)module_get_data(this_module);
    data->comm_master_trigger_down();
}
