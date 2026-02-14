/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : tx.h
  * @brief          : Header file for SYSCOM TX main functions
  ******************************************************************************
  */

#ifndef MDC_MODULES_SYSCOM_IMPL_TX_H
#define MDC_MODULES_SYSCOM_IMPL_TX_H

#include <msg/defs/Frame.h>
#include <msg/defs/Message.h>
#include <main/module.h>

struct tx_context
{
    uint8_t buffer[FRAME_SIZE];
    Message status_to_send;
};

void tx_start(struct module *this_mod, struct tx_context *context);

void tx_work(struct module *this_mod, struct tx_context *context);
void tx_callback(struct module *this_mod, struct tx_context *context);

#endif // MDC_MODULES_SYSCOM_IMPL_TX_H
