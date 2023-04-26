/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : msg_distributor.h
  * @brief          : <brief>
  ******************************************************************************
  */
#ifndef MDC_RX_IMPL_MSG_DISTRIBUTOR_H
#define MDC_RX_IMPL_MSG_DISTRIBUTOR_H

#include <msg/defs/Message.h>

#include <cmsis_os2.h>

void configureMsgDistributor(osMessageQueueId_t* messageQueueHandle);

void forwardMessage(const Message* msg);

#endif //MDC_RX_IMPL_MSG_DISTRIBUTOR_H
