/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <MDC/feedback/interface.h>

#include <MDC/feedback/impl/feedback.h>

void configure_feedback()
{
    configure_feedback_impl();
}

void work_feedback()
{
    work_feedback_impl();
}

void periodical_callback_controller()
{
    periodical_callback_controller_impl();
}

void on_ext_interrupt_feedback(uint16_t GPIO_Pin)
{
    on_ext_interrupt_feedback_impl(GPIO_Pin);
}
