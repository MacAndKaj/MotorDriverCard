/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_controller.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_COM_MESSAGE_CONTROL_H
#define MDC_COM_MESSAGE_CONTROL_H

#include <msg/consts.h>
#include <msg/defs/Message.h>
#include <ICI/interthread_com_if_params.h>

#include <stdint.h>

struct MessageControl
{
    uint8_t nextReadMessageId;
    InterThreadComIfParams interThreadComIfParams;
};
typedef struct MessageControl MessageControl;

void forwardMessage(MessageControl* messageControl, const Message* msg);

#endif //MDC_COM_MESSAGE_CONTROL_H
