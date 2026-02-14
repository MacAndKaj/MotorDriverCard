/**
  * Copyright (c) 2023 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : Frame.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_APP_MSG_DEFS_FRAME_H
#define MOTORDRIVER_APP_MSG_DEFS_FRAME_H

#include <stdint.h>

#define DATA_SIZE 125
#define HEADER_BYTE 0xF0

struct Frame
{
    uint8_t header;
    uint8_t id;
    uint8_t data[DATA_SIZE];
    uint8_t crc;
};

typedef struct Frame Frame;

#define FRAME_SIZE sizeof(Frame)
#define FRAME_DATA_OFFSET (sizeof(Frame::header) + sizeof(Frame::id))

#endif // MOTORDRIVER_APP_MSG_DEFS_FRAME_H
