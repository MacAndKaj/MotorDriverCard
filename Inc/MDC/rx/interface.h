/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_RX_INTERFACE_H
#define MDC_RX_INTERFACE_H

/// Function to configure RxTask
void configureRx();

/// Callback when new data was received and should be dispatched
void onReceptionCompleted();

#endif //MDC_RX_INTERFACE_H
