/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface of log task.
  ******************************************************************************
  */

#include "modules/log/interface.h"

#include "modules/log/impl/log.h"

#include <memory.h>
#include <stdarg.h>

void configure_log(osMutexId_t* logMutex, transmit_func f)
{
    set_log_mutex(logMutex);
    set_transmit_function(f);
    LOG_INFO("[log] Logger is working\n");
}

void logger(const char* logStr)
{
    send_log(logStr, (int)strlen(logStr));
}

void logger_args(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    send_log_variadic(message, args);
    va_end(args);
}

void logger_transfer_complete_callback(void)
{
    unlock_mutex();
}
