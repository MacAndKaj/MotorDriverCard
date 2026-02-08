/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : Header for interface of Syscom module.
  *                   This file contains interface declarations for using Syscom module.
  ******************************************************************************
  */
#ifndef MDC_TASKS_SYSCOM_INTERFACE_H
#define MDC_TASKS_SYSCOM_INTERFACE_H

#include <cmsis_os2.h>

#define SYSCOM_SPI_COMM_INDEX 0

struct module;
struct syscom_internal_data;

typedef void (*comm_master_trigger_ctrl_func_t)(void);

struct syscom_data
{
    osThreadId_t* syscom_thread_handle;
    osMessageQueueId_t* transferred_messages_queue_handle;
    osTimerId_t* syscom_timer_handle;
    struct message_subscription *subs;
    int subs_len;
    comm_master_trigger_ctrl_func_t comm_master_trigger_up;
    comm_master_trigger_ctrl_func_t comm_master_trigger_down;
    struct syscom_internal_data *internal_data_handle;
};

void syscom_module_init(struct module *syscom_module);
void syscom_module_timer_callback(struct module *this_module);
void syscom_transfer_finished_callback(struct module* this_module);

#endif // MDC_TASKS_SYSCOM_INTERFACE_H
