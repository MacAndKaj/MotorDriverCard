/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : init_interrupt_service.h
  * @brief          : Sources for init.h file.
  *                   This file contains definitions of init functions.
  ******************************************************************************
  */

#ifndef MOTORDRIVERCARD_INTERRUPT_SERVICE_H
#define MOTORDRIVERCARD_INTERRUPT_SERVICE_H

#include <stdint.h>

/// Function to dispatch interrupt. Must be called in ISR.
/// \param GPIO_Pin Pin that interrupt comes from.
void dispatch_interrupt(uint16_t GPIO_Pin);

struct InterruptServiceInterface
{
    int (*subscribeForInterrupt)(uint16_t GPIO_Pin, void (*handler)(void));
};

/// Initializes InterruptService.
struct InterruptServiceInterface init_interrupt_service();

#endif //MOTORDRIVERCARD_INTERRUPT_SERVICE_H
