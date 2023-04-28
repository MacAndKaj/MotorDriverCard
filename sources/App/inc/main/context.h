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

#include "tim.h"
#include "usart.h"

#include <stdint.h>

struct Context
{
    void (*extInterruptCb)(uint16_t GPIO_Pin);
    void (*rxCompletedCb)(UART_HandleTypeDef* huart);
    void (*periodElapsedCb)(TIM_HandleTypeDef *htim);
};

/// Creates new context structure and initializes it.
/// \return Ptr to new Context structure.
struct Context* new_main_context();

///// Returns saved main context
///// \return ptr to struct Context - main context
//struct Context* get_main_context()

#endif //MOTORDRIVERCARD_CONTEXT_H
