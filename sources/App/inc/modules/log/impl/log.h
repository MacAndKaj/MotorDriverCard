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

#include <modules/log/interface.h>

#include <cmsis_os2.h>

void set_log_mutex(osMutexId_t* logMutex);

void set_transmit_function(transmit_func f);

void send_log(const char *ptr, int len);

void send_log_variadic(const char *ptr, ...);

void unlock_mutex(void);

#endif // LOG_IMPL_LOG_H
