/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : context.c
  * @brief          : Sources for context.h file.
  *                   This file contains definitions of init functions.
  ******************************************************************************
  */
#include "main/context.h"
#include "main/init.h"

#include <stdbool.h>

void handle_ext_interrupt(uint16_t GPIO_Pin);
void handle_rx_completed(UART_HandleTypeDef* huart);
void handle_period_elapsed(TIM_HandleTypeDef *htim);

struct Context mainContext;
bool contextInitialized = false;

struct Context* new_main_context()
{
    mainContext.extInterruptCb = handle_ext_interrupt;
    mainContext.rxCompletedCb = handle_rx_completed;
    mainContext.periodElapsedCb = handle_period_elapsed;
    contextInitialized = true;

    return &mainContext;
}

//struct Context* get_main_context()
//{
//    return mainContext;
//}

//=====================================
//TODO: update with service handling
void handle_ext_interrupt(uint16_t GPIO_Pin)
{
  onExtInterrupt(GPIO_Pin);
}

void handle_rx_completed(UART_HandleTypeDef* huart)
{
  onRxCpltCallback(huart);
}

void handle_period_elapsed(TIM_HandleTypeDef *htim)
{
  onPeriodElapsedCallback(htim);
}
//=====================================
