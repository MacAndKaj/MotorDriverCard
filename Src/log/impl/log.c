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

#define TIMEOUT 1000

int _write(int file, char *ptr, int len)
{
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }

    // arbitrary timeout 1000
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, TIMEOUT);

    return (status == HAL_OK ? len : 0);
}