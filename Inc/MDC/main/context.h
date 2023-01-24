/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : context.h
  * @brief          :
  ******************************************************************************
  */

#ifndef MOTORDRIVERCARD_CONTEXT_H
#define MOTORDRIVERCARD_CONTEXT_H

#include <MDC/main/services/interrupt_service.h>

#include <stdint.h>

struct Context
{
    struct InterruptServiceInterface interrupt_service_interface;
};

/// Creates new context structure and initializes it.
/// \return Ptr to new Context structure.
struct Context* new_context();

#endif //MOTORDRIVERCARD_CONTEXT_H
