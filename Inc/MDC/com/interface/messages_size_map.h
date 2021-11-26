/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : messages_size_map.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_MESSAGES_SIZE_MAP_H
#define MOTORDRIVER_MESSAGES_SIZE_MAP_H

#include <MDC/com/interface/message_ids.h>

#include <stdint.h>

typedef struct
{
    uint8_t id;
    uint16_t size;
} Node;

extern Node map[MESSAGES_NUM];

uint16_t findSizeForMessageId(uint8_t id);

#endif //MOTORDRIVER_MESSAGES_SIZE_MAP_H
