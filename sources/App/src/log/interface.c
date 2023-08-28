/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface of log task.
  ******************************************************************************
  */

#include "log/interface.h"

#include "log/impl/log.h"

#include <memory.h>

void configure_log(osMutexId_t* logMutex)
{
    set_log_mutex(logMutex);
}

void logger(const char* logStr)
{
    send_log(logStr, (int)strlen(logStr));
}
