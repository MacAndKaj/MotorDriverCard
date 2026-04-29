/**
  * Copyright (c) 2026 MacAndKaj. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : Interface for scan module
  ******************************************************************************
  */
#ifndef MDC_MODULES_SCAN_INTERFACE_H
#define MDC_MODULES_SCAN_INTERFACE_H

#include <stm32f3xx_hal.h>
#include <cmsis_os2.h>

struct module;
struct scan_internal_data;

typedef void (*start_tim_pwm_func_t)(uint16_t*);
typedef void (*set_gpio_func_t)(uint8_t);

struct scan_data
{
    osThreadId_t *scan_thread_handle;
    start_tim_pwm_func_t start_pwm;
    set_gpio_func_t set_trigger_gpio;
    struct scan_internal_data *internal_data;
};

void scan_module_init(struct module *this_module);

#endif //MDC_MODULES_SCAN_INTERFACE_H
