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

typedef void (*uart_handler_t)(UART_HandleTypeDef*);
typedef void (*tim_handler_t)(TIM_HandleTypeDef*);
typedef void (*spi_handler_t)(SPI_HandleTypeDef*);
typedef void (*gpio_exti_handler_t)(uint16_t);
typedef void (*module_work_handler_t)(struct module*);
typedef int (*read_func_t)(uint8_t*, uint16_t);
typedef int (*write_func_t)(uint8_t*, uint16_t);
typedef int (*write_and_read_func_t)(uint8_t*, uint8_t*, uint16_t);
typedef void (*start_tim_func_t)();

/**
 * @brief Structure containing callbacks for events occuring on UART peripheral.
 * 
 */
struct uart_module_handlers
{
    uart_handler_t handle_tx_cplt;
    uart_handler_t handle_rx_cplt;
    uart_handler_t handle_tx_half_cplt;
    uart_handler_t handle_rx_half_cplt;
};

/**
 * @brief Structure containing callbacks for events occuring on SPI peripheral.
 * 
 */
struct spi_module_handlers
{
    spi_handler_t handle_tx_cplt;
    spi_handler_t handle_rx_cplt;
    spi_handler_t handle_tx_rx_cplt;
    spi_handler_t handle_tx_half_cplt;
    spi_handler_t handle_rx_half_cplt;
    spi_handler_t handle_tx_rx_half_cplt;
};

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
    struct uart_module_handlers uart_handlers;
    struct spi_module_handlers spi_handlers;
    struct tim_module_handlers tim_handlers;

    // Peripherals communication operations
    struct comm_ops *communication_ops;

    struct tim_ops *timers_ops;

    module_work_handler_t work_ops;
};

struct module
{
    struct module_ops ops; // currently only one module_ops is possible, TODO: change to map of modules used
    void *data;
};

#define MODULE_WORK(mod) (mod)->ops.work_ops(mod)


static inline void * module_get_data(const struct module *mod)
{
	return mod->data;
}

static inline void module_set_data(struct module *mod, void *data)
{
	mod->data = data;
}

#endif //MDC_MAIN_MODULE_H
