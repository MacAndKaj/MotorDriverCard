/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : <brief>
  ******************************************************************************
  */
#ifndef MDC_MODULES_CONTROLLER_INTERFACE_H
#define MDC_MODULES_CONTROLLER_INTERFACE_H

#include <stm32f3xx_hal.h>

#include <cmsis_os.h>

struct module;
struct controller_internal_data;

typedef void (*start_tim_pwm_dma_func_t)(uint32_t *);

struct motor_pinout
{
    GPIO_TypeDef *motorControl1Port;
    uint16_t      motorControl1Pin;
    GPIO_TypeDef *motorControl2Port;
    uint16_t      motorControl2Pin;
};

struct motor_info
{
    struct motor_pinout pinout;
    start_tim_pwm_dma_func_t start_pwm;
};

struct controller_data
{
    osThreadId_t        *controller_thread_handle;
    osMessageQueueId_t  *message_queue_handle;
    osMessageQueueId_t  *speed_values_queue_handle;
    struct motor_info   *left_motor_info;
    struct motor_info   *right_motor_info;
    struct controller_internal_data *internal_data;
};

void controller_module_init(struct module *this_module);
void controller_module_work(struct module *this_module);
// TODO EXT callback

#endif //MDC_MODULES_CONTROLLER_INTERFACE_H
