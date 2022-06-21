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


#define LOG_INFO(MSG) \
    logger("[INFO]"MSG)

#define LOG_INFO_V(MSG, ...) \
    logger_args("[INFO]"MSG, __VA_ARGS__)

void logger(const char* logStr);
void logger_args(const char* logStr, ...);

#endif //LOG_INTERFACE_H
