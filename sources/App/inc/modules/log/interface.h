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

typedef void (*transmit_func)(const char *ptr, int len);

#define LOG_INFO(MSG) \
    logger("[INFO]"MSG)

// #define LOG_INFO_ARGS(MSG, ARGS...) printf("[INFO]"MSG, ARGS)
#define LOG_INFO_ARGS(MSG, ARGS...) logger_args("[INFO]"MSG, ARGS)

void configure_log(osMutexId_t* logMutex, transmit_func f);

void logger(const char* logStr);

void logger_args(const char* message, ...);

void logger_transfer_complete_callback(void);

#endif //LOG_INTERFACE_H
