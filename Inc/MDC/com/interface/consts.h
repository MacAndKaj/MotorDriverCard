/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : consts.h
  * @brief          : Header for constants of platform interface.
  *                   This file contains definitions of constants.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_CONSTS_H
#define MOTORDRIVER_CONSTS_H

// Message status begin
enum Status
{
    NoError,
    UndefinedError
};
// Message status end

// Message status begin
enum DataType
{
    FrameCtrlData,
    UserData
};
// Message status end

#define FRAME_CTRL_DATA_SIZE 1
#define MESSAGE_CTRL_DATA_SIZE 1
#define HEADER_SIZE FRAME_CTRL_DATA_SIZE + MESSAGE_CTRL_DATA_SIZE

#define FRAME_CTRL_DATA 0xF0

#endif //MOTORDRIVER_CONSTS_H
