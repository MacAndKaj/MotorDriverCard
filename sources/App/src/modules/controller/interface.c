/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : <brief>
  ******************************************************************************
  */
#include <modules/controller/interface.h>

#include <modules/controller/impl/controller.h>
#include <modules/controller/impl/motor_process.h>
#include <main/module.h>

static struct controller_internal_data internal_data;

void controller_module_work(struct module *this_module)
{
    struct controller_data *data = (struct controller_data *)module_get_data(this_module);
    controller_work(data);
}

void controller_module_init(struct module *this_module)
{
    struct controller_data *data = (struct controller_data *)module_get_data(this_module);
    data->internal_data = &internal_data;
    
    this_module->ops.work_ops = controller_module_work;
    controller_init(data);
}
