/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interthread_com_if_params.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef ICI_INTERTHREAD_COM_IF_PARAMS_H
#define ICI_INTERTHREAD_COM_IF_PARAMS_H

#include <cmsis_os2.h>

#define FLAG_SET 0x00000001U

typedef struct
{
    osEventFlagsId_t messageReceivedFlagsId;
    osMessageQueueId_t messageQueueId;
} InterThreadComIfParams;

#endif //ICI_INTERTHREAD_COM_IF_PARAMS_H
