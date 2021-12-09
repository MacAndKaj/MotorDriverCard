/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : receiver.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_RX_IMPL_RECEIVER_H
#define MDC_RX_IMPL_RECEIVER_H

#define DATA_RECEIVED_THREAD_FLAG 0x00000001

void configureReceiver(osThreadId_t* rxThreadId);

void startReception(uint8_t* dest, uint16_t N);

#endif //MDC_RX_IMPL_RECEIVER_H
