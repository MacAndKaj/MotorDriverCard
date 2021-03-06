/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface of log task.
  ******************************************************************************
  */

#include <log/interface.h>

#include <log/impl/log.h>

#include <stdio.h>
#include <stdarg.h>

void logger(const char* logStr)
{
    printf(logStr);
}

void logger_args(const char* logStr, ...)
{
    va_list args1;
    va_start(args1, logStr);
    vprintf(logStr, args1);
    va_end(args1);
}
