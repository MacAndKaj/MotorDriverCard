/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include "modules/log/interface.h"

#include <modules/feedback/interface.h>

#include <main/module.h>
#include <modules/feedback/impl/defs.h>
#include <modules/feedback/impl/feedback.h>

#include "main/defs.h"

#define MPU_9255_I2C_ADDR (0x68 << 1)   // MPU-9250 I2C address shifted left by 1 for HAL functions
#define ACCEL_AND_GYRO_DATA_START 0x3B
#define WHO_AM_I_REG 0x75
#define WHO_AM_I_VALUE 0x73


void feedback_module_work(struct module *this_mod)
{
    osThreadFlagsWait(PROBING_TIMEOUT_CALLBACK, osFlagsWaitAny, osWaitForever);
    struct feedback_data *data = module_get_data(this_mod);

    feedback_work(data, PROBING_TIMEOUT_CALLBACK);

    const struct ext_dev_ops *ops = this_mod->ops.external_devices_ops;
    ops->read_ext_dev_mem(MPU_9255_I2C_ADDR, ACCEL_AND_GYRO_DATA_START, data->accel_and_gyro_data_buffer, ACCEL_AND_GYRO_DATA_SIZE);
    feedback_work(data, IMU_DATA_READY_FLAG);
}

void feedback_module_init(struct module *this_module)
{
    struct feedback_data *data = module_get_data(this_module);
    struct module_ops *ops = &this_module->ops;
    ops->work_ops = feedback_module_work;
    feedback_start(data);
    ops->timers_ops[FEEDBACK_TIMER_INDEX].start_tim();

    uint8_t who_am_i_buffer = 0;
    ops->external_devices_ops->read_ext_dev_mem(MPU_9255_I2C_ADDR, WHO_AM_I_REG, &who_am_i_buffer, 1);
    if (who_am_i_buffer != WHO_AM_I_VALUE)
    {
        LOG_INFO_ARGS("[feedback] IMU not detected, who_am_i: 0x%02x\n", who_am_i_buffer);
    }
}

void feedback_timer_callback(struct module *this_module)
{
    struct feedback_data *data = module_get_data(this_module);
    feedback_update(data);
}
