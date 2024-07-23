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

#include <FreeRTOS.h>

#include <memory.h>
#include <stdarg.h>

void configure_log(osMutexId_t* logMutex)
{
    set_log_mutex(logMutex);
}

void logger(const char* logStr)
{
    send_log(logStr, (int)strlen(logStr));
}

void logger_args(const char* message, ...)
{
    va_list args;
    send_log_variadic(message, args);
}