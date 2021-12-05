/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : CommunicationContext.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_COM_COMMUNICATIONCONTEXT_H
#define MDC_COM_COMMUNICATIONCONTEXT_H

#include <MDC/com/impl/message_control.h>

#include <stdint.h>

struct RxBuffer
{
    uint8_t newData;
    uint8_t *data;
    enum DataType nextRead;
};
typedef struct RxBuffer RxBuffer;

struct CommunicationContext
{
    RxBuffer rxBuffer;
    MessageControl msgControl;
};
typedef struct CommunicationContext CommunicationContext;

#endif //MDC_COM_COMMUNICATIONCONTEXT_H
