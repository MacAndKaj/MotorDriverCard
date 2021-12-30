/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : log.h
  * @brief          : This file contains implementation declarations and definitons for logger.
  ******************************************************************************
  */
#ifndef MOTORDRIVERCARD_LOG_IMPL_LOG_H
#define MOTORDRIVERCARD_LOG_IMPL_LOG_H

#include <cmsis_os2.h>

uint32_t getLogMessageSizeImpl();

void configureLogImpl(osMessageQueueId_t* messageQueueHandle, osThreadId_t* threadIdHandle);

void workLogImpl();

void logImpl(const char* severityStr, const char* characters, ...);

#endif // MOTORDRIVERCARD_LOG_IMPL_LOG_H
