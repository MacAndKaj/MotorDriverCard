/**
  * Copyright (c) 2024 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : module.h
  * @brief          :
  ******************************************************************************
  */

#ifndef MDC_MAIN_MODULE_H
#define MDC_MAIN_MODULE_H

#include "gpio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

struct module;

typedef void (*tim_handler_t)(TIM_HandleTypeDef*);
typedef void (*gpio_exti_handler_t)(uint16_t);
typedef void (*module_work_handler_t)(struct module*);
typedef int (*read_func_t)(uint8_t*, uint16_t);
typedef int (*write_func_t)(uint8_t*, uint16_t);
typedef int (*write_and_read_func_t)(uint8_t*, uint8_t*, uint16_t);
typedef void (*start_tim_func_t)();
typedef uint32_t (*calculate_crc_func_t)(uint8_t *buf, size_t len);
typedef int (*read_ext_dev_mem_func_t)(uint8_t, uint8_t, uint8_t*, uint16_t);

/**
 * @brief Structure containing callbacks for events occuring on TIM peripheral.
 * 
 */
struct tim_module_handlers
{
    tim_handler_t handle_period_elapsed;
    tim_handler_t handle_period_elapsed_half_cplt;
};

struct comm_ops
{
    read_func_t read_blocking;
    write_func_t write_blocking;
    read_func_t read_non_blocking;
    write_func_t write_non_blocking;
    write_and_read_func_t write_and_read_blocking;
    write_and_read_func_t write_and_read_non_blocking;
    calculate_crc_func_t calculate_crc;
};

struct ext_dev_ops
{
    read_ext_dev_mem_func_t read_ext_dev_mem;
    read_ext_dev_mem_func_t read_ext_dev_mem_non_blocking;
};

struct tim_ops
{
    start_tim_func_t start_tim;
};

/**
 * @brief Basic module structure containing all supported operations. If not supported operation is NULL.
 * 
 */

struct module_ops
{
    // Peripherals callback handlers
    gpio_exti_handler_t handle_ext_int;
    struct tim_module_handlers tim_handlers;

    // Peripherals communication operations
    struct comm_ops *communication_ops;
    struct ext_dev_ops *external_devices_ops;

    struct tim_ops *timers_ops;

    module_work_handler_t work_ops;
};

struct module
{
    struct module_ops ops; // currently only one module_ops is possible, TODO: change to map of modules used
    void *data;
};

#define MODULE_WORK(mod) (mod)->ops.work_ops(mod)


inline void * module_get_data(const struct module *mod)
{
	return mod->data;
}

inline void module_set_data(struct module *mod, void *data)
{
	mod->data = data;
}

#endif //MDC_MAIN_MODULE_H
