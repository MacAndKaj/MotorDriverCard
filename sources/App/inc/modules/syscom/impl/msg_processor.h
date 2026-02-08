/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : msg_processor.h
  * @brief          : <brief>
  ******************************************************************************
  */
#ifndef MDC_MODULES_SYSCOM_IMPL_MSG_PROCESSOR_H
#define MDC_MODULES_SYSCOM_IMPL_MSG_PROCESSOR_H

#include <stdint.h>

#include "msg/defs/Frame.h"

struct Message* process_data(const uint8_t* frame_data);

void process_message(const struct Message* message, uint8_t buffer[FRAME_SIZE]);

#endif // MDC_MODULES_SYSCOM_IMPL_MSG_PROCESSOR_H
