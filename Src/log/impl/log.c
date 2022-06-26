/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Sources for interface.h file.
  ******************************************************************************
  */
#include <usart.h>

#include <errno.h>
#include <sys/unistd.h>
#include <cmsis_os2.h>

#define TIMEOUT 100

static osMutexId_t* logMutexPtr = NULL;

void set_log_mutex(osMutexId_t* logMutex)
{
    logMutexPtr = logMutex;
}

int _write(int file, char *ptr, int len)
{
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }

    osMutexAcquire(*logMutexPtr, osWaitForever);
    // arbitrary timeout 1000
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart4, (uint8_t*)ptr, len, TIMEOUT);
    osMutexRelease(*logMutexPtr);

    return (status == HAL_OK ? len : 0);
}