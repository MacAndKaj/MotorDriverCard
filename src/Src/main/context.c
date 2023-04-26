/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : context.c
  * @brief          : Sources for context.h file.
  *                   This file contains definitions of init functions.
  ******************************************************************************
  */
#include <main/context.h>
#include <main/init.h>

#include <malloc.h>

void handle_ext_interrupt(uint16_t GPIO_Pin);
void handle_rx_completed(UART_HandleTypeDef* huart);
void handle_period_elapsed(TIM_HandleTypeDef *htim);

struct Context* mainContext = NULL;

struct Context* new_main_context()
{
    struct Context* ret;
    ret = malloc(sizeof(struct Context));

    ret->interrupt_service_interface = init_interrupt_service();
    ret->extInterruptCb = handle_ext_interrupt;
    ret->rxCompletedCb = handle_rx_completed;
    ret->periodElapsedCb = handle_period_elapsed;

    mainContext = ret;
    return ret;
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
