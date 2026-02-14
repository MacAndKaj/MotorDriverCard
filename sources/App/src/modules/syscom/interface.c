/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Source file for interface of Syscom module.
  *                   This file contains interface definitions for using Syscom module.
  ******************************************************************************
  */

#include "modules/log/interface.h"

#include <modules/syscom/interface.h>

#include <main/defs.h>
#include <main/module.h>
#include <modules/syscom/impl/rx.h>
#include <modules/syscom/impl/tx.h>

#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "portmacro.h"

#define SYSCOM_WORK_TICKS pdMS_TO_TICKS(2) // 2ms
#define FRAME_PREPARATION_OFFSET_TICKS pdMS_TO_TICKS(8) // 8ms, time between frame received and response status prepared

// #define SYSCOM_WORK_TICKS (2) // 2ms
// #define FRAME_PREPARATION_OFFSET_TICKS (8) // 8ms, time between frame received and response status prepared

struct syscom_internal_data
{
    struct rx_context rx_ctx;
    struct tx_context tx_ctx;
};

static struct syscom_internal_data internal_data;

void syscom_module_work(struct module *this_mod)
{
    osThreadFlagsWait(DATA_TX_RX_TRANSFERRED_THREAD_FLAG, osFlagsWaitAll | osFlagsNoClear, SYSCOM_WORK_TICKS);

    if (osThreadFlagsGet() & DATA_TX_RX_TRANSFERRED_THREAD_FLAG)
    {
        // struct syscom_data *data = module_get_data(this_mod);
        // int status = osTimerStart(*data->syscom_timer_handle, FRAME_PREPARATION_OFFSET_TICKS);
        // if (status != osOK)
        // {
        //     LOG_INFO_ARGS("[syscom][rx] Error when starting timer, status: %d\n", status);
        // }
        rx_work(this_mod, &internal_data.rx_ctx);
        this_mod->ops.communication_ops->write_and_read_non_blocking(
            internal_data.tx_ctx.buffer, internal_data.rx_ctx.buffer, FRAME_SIZE);
        osThreadFlagsClear(DATA_TX_RX_TRANSFERRED_THREAD_FLAG);
    }
    tx_work(this_mod, &internal_data.tx_ctx);
}

void syscom_module_init(struct module *syscom_module)
{
    struct syscom_data *data = module_get_data(syscom_module);
    data->internal_data_handle = &internal_data;
    
    syscom_module->ops.work_ops = syscom_module_work;

    rx_start(syscom_module, &internal_data.rx_ctx);
    tx_start(syscom_module, &internal_data.tx_ctx);

    syscom_module->ops.communication_ops->write_and_read_non_blocking(
        internal_data.tx_ctx.buffer, internal_data.rx_ctx.buffer, FRAME_SIZE);
}

void syscom_module_timer_callback(struct module *this_module)
{
    tx_callback(this_module, &internal_data.tx_ctx);
}
