/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_FEEDBACK_INTERFACE_H
#define MDC_FEEDBACK_INTERFACE_H

#include <stdint.h>

void configure_feedback();

void work_feedback();

void periodical_callback_controller();

void on_ext_interrupt_feedback(uint16_t GPIO_Pin);

#endif //MDC_FEEDBACK_INTERFACE_H
