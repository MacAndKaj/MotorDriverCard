/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.c
  * @brief          : <brief>
  ******************************************************************************
  */

#include <MDC/rx/impl/rx.h>

void configureRx()
{
    configureRxImpl();
}

void onReceptionCompleted()
{
    onReceptionCompletedImpl();
}
