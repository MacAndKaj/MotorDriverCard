/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_MODULES_SYSCOM_IMPL_RX_H
#define MDC_MODULES_SYSCOM_IMPL_RX_H

#include <msg/defs/Frame.h>
#include <main/module.h>

struct rx_context
{
    uint8_t buffer[FRAME_SIZE];
};

void rx_start(struct module *this_mod, struct rx_context *context);

void rx_work(struct module *this_mod, struct rx_context *context);

#endif // MDC_MODULES_SYSCOM_IMPL_RX_H
