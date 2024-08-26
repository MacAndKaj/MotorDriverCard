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

#include <cmsis_os.h>

#define SYSCOM_SPI_COMM_INDEX 0

struct module;
struct syscom_internal_data;

struct syscom_data
{
    osThreadId_t* syscom_thread_handle;
    osMessageQueueId_t* received_messages_queue_handle;
    struct syscom_internal_data *internal_data_handle;
};

void syscom_module_init(struct module *syscom_module);


#endif // MDC_TASKS_SYSCOM_INTERFACE_H
