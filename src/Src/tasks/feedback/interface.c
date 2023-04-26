/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <tasks/feedback/interface.h>

#include <tasks/feedback/impl/feedback.h>

void configure_feedback(const struct FeedbackConfig* config)
{
    configure_feedback_impl(config->speedMeasQueueHandle, config->feedbackThreadIdHandle);
}

void work_feedback()
{
    work_feedback_impl();
}

void periodical_callback_feedback()
{
    periodical_callback_feedback_impl();
}

void on_ext_interrupt_feedback(uint16_t GPIO_Pin)
{
    on_ext_interrupt_feedback_impl(GPIO_Pin);
}
