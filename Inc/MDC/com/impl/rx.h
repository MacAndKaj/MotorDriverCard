/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : com.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_COM_COM_H
#define MDC_COM_COM_H

#include <MDC/com/impl/communication_context.h>

#include <usart.h>

void configureComImpl();
void workCom();

void comReceiveCallback(UART_HandleTypeDef *huart);

#endif //MDC_COM_COM_H
