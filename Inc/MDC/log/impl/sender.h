/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : sender.h
  * @brief          : Header for sender.c file.
  ******************************************************************************
  */

#ifndef MOTORDRIVERCARD_LOG_IMPL_SENDER_H
#define MOTORDRIVERCARD_LOG_IMPL_SENDER_H

#include <cmsis_os2.h>

void configureSender(osThreadId_t* threadIdHandle);

int send(uint8_t *bytes, uint8_t count);

void onTransmitCompletedImpl();

#endif //MOTORDRIVERCARD_LOG_IMPL_SENDER_H
