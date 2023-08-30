/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface.h file.
  ******************************************************************************
  */
#include "usart.h"

#include <errno.h>
#include <sys/unistd.h>
#include <cmsis_os2.h>

#define TIMEOUT 100

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

int _write(int file, char *ptr, int len)
{
    send_log(ptr, len);
	return len;
}