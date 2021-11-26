/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : log.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <MDC/main/log.h>

#include <usart.h>

#include <string.h>
#include <errno.h>
#include <sys/unistd.h>

uint8_t characters[MAX_LOG_LENGTH];

void initLog()
{
    memset(characters, (uint8_t)'?', MAX_LOG_LENGTH);
}

int _write(int file, char *ptr, int len)
{
    memcpy(characters, ptr, len);

    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }

    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart3, characters, len, 100);

    return (status == HAL_OK ? len : 0);
}
