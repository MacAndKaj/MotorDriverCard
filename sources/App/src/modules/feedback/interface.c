/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <modules/feedback/interface.h>

#include <main/module.h>
#include <modules/feedback/impl/defs.h>
#include <modules/feedback/impl/feedback.h>

void feedback_module_work(struct module *this_mod)
{
    osThreadFlagsWait(PROBING_TIMEOUT_CALLBACK, osFlagsWaitAny, osWaitForever);
    struct feedback_data *data = (struct feedback_data *)module_get_data(this_mod);
    feedback_work(data);
}

void feedback_module_init(struct module *this_module)
{
    struct feedback_data *data = (struct feedback_data *)module_get_data(this_module);

    this_module->ops.work_ops = feedback_module_work;
    feedback_start(data);
    this_module->ops.timers_ops[FEEDBACK_TIMER_INDEX].start_tim();
}

void feedback_timer_callback(struct module *this_module)
{
    struct feedback_data *data = (struct feedback_data *)module_get_data(this_module);
    feedback_update(data);
}
