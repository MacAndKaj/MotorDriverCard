/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Source file for interface of monitoring module.
  *                   This file contains interface definitions for using monitoring module.
  ******************************************************************************
  */

#include <modules/monitoring/interface.h>

#include <main/module.h>
#include <modules/monitoring/impl/monitoring.h>
  
void monitoring_module_work(struct module *this_mod)
{
    monitoring_work((struct monitoring_data *)module_get_data(this_mod));
}

void monitoring_module_init(struct module *this_mod)
{
    this_mod->ops.work_ops = monitoring_module_work;
    monitoring_init((struct monitoring_data *)module_get_data(this_mod));
}
