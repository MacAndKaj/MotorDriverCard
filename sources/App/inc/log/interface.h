/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : This file contains interface of log task and its functionalities
  ******************************************************************************
  */
#ifndef LOG_INTERFACE_H
#define LOG_INTERFACE_H

#include <cmsis_os2.h>

#include <stdio.h>

#define LOG_INFO(MSG) \
    logger("[INFO]"MSG)

#define LOG_INFO_ARGS(MSG, ARGS...) printf("[INFO]"MSG, ARGS)

void configure_log(osMutexId_t* logMutex);

void logger(const char* logStr);

#endif //LOG_INTERFACE_H
