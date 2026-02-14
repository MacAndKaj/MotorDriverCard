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

#include <msg/defs/PlatformStatus.h>

#include <stdint.h>

typedef struct InternalMessage InternalMessage;
typedef struct Message Message;

Message* process_data(const uint8_t* frame_data);

void process_message(const InternalMessage *src_msg, PlatformStatus* dest_msg);

void prepare_frame(const Message* status, uint8_t* out_buf);

#endif // MDC_MODULES_SYSCOM_IMPL_MSG_PROCESSOR_H
