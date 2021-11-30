/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : def.h
  * @brief          : This file contains implementation declarations and definitons for logger.
  ******************************************************************************
  */
#ifndef MOTORDRIVERCARD_LOG_IMPL_DEF_H
#define MOTORDRIVERCARD_LOG_IMPL_DEF_H

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#define MAX_LINE_LENGTH 140

#define TRANSFER_COMPLETED_FLAG 0x0001

#endif // MOTORDRIVERCARD_LOG_IMPL_DEF_H
