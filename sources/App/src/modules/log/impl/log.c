/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface.h file.
  ******************************************************************************
  */
#include "modules/log/impl/log.h"

#include <cmsis_os2.h>

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define BUFFER_SIZE 150ul

static osMutexId_t* logMutexPtr = NULL;
static transmit_func write_log = NULL;
static char log_buffer[BUFFER_SIZE] = {0};

void set_log_mutex(osMutexId_t* logMutex)
{
    logMutexPtr = logMutex;
}

void set_transmit_function(transmit_func f)
{
    write_log = f;
}

void send_log(const char *ptr, int len)
{
    osMutexAcquire(*logMutexPtr, osWaitForever);
    memcpy(log_buffer, ptr, len);
    if (write_log != NULL)
    {
        write_log(log_buffer, len);
    }
    osMutexRelease(*logMutexPtr);
}

int _write(int file, char *ptr, int len)
{
    (void)file;
    send_log(ptr, len);
	return len;
}

void send_log_variadic(const char *ptr, va_list arguments)
{
    static char buffer[BUFFER_SIZE] = {0};

    int32_t len = vsnprintf(buffer, BUFFER_SIZE, ptr, arguments);

    send_log(buffer, len);
}