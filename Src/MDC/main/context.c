/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : context.c
  * @brief          : Sources for context.h file.
  *                   This file contains definitions of init functions.
  ******************************************************************************
  */
#include <MDC/main/context.h>
#include <malloc.h>


struct Context* new_context()
{
    struct Context* ret;
    ret = malloc(sizeof(struct Context));

    ret->interrupt_service_interface = init_interrupt_service();

    return ret;
}

