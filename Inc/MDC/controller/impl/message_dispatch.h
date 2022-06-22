/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_dispatch.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_CONTROLLER_IMPL_MESSAGE_DISPATCH_H
#define MDC_CONTROLLER_IMPL_MESSAGE_DISPATCH_H

struct Message;

void message_dispatch_onMessageReceived(const struct Message* msg);

#endif //MDC_CONTROLLER_IMPL_MESSAGE_DISPATCH_H
