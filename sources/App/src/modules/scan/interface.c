/**
  * Copyright (c) 2026 MacAndKaj. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Implementation of scan module interface
  ******************************************************************************
  */
#include <modules/scan/interface.h>

#include <modules/scan/impl/scan.h>
#include <main/module.h>

static struct scan_internal_data internal_data;

void scan_module_work(struct module *this_module)
{
    struct scan_data *data = module_get_data(this_module);
    scan_work(data);
}

void scan_module_init(struct module *this_module)
{
    struct scan_data *data = module_get_data(this_module);
    data->internal_data = &internal_data;

    this_module->ops.work_ops = scan_module_work;
    scan_init(data);
}
