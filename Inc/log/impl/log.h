/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : log.h
  * @brief          : This file contains implementation declarations and definitons for logger.
  ******************************************************************************
  */
#ifndef LOG_IMPL_LOG_H
#define LOG_IMPL_LOG_H

#include <cmsis_os2.h>

void set_log_mutex(osMutexId_t* logMutex);

int _write(int file, char *ptr, int len);

#endif // LOG_IMPL_LOG_H
