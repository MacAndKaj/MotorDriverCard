/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface.h file.
  ******************************************************************************
  */
#include "modules/log/impl/log.h"

#include "usart.h"

#include <cmsis_os2.h>

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#define TIMEOUT 100
#define BUFFER_SIZE 150ul

static osMutexId_t* logMutexPtr = NULL;

void set_log_mutex(osMutexId_t* logMutex)
{
    logMutexPtr = logMutex;
}

void send_log(const char *ptr, int len)
{
    osMutexAcquire(*logMutexPtr, osWaitForever);
    // arbitrary timeout 1000
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, TIMEOUT);
    if (status != HAL_OK)
    {
        Error_Handler();
    }
    osMutexRelease(*logMutexPtr);
}

int _write(int /*file*/, char *ptr, int len)
{
    send_log(ptr, len);
	return len;
}

void send_log_variadic(const char *ptr, ...)
{
    static char buffer[BUFFER_SIZE] = {};
    va_list arguments;
    va_start(arguments, ptr);

    int32_t len = vsnprintf(buffer, BUFFER_SIZE, ptr, arguments);

    send_log(buffer, len);

    va_end(arguments);
}
