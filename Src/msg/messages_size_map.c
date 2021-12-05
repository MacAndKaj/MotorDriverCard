/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : messages_size_map.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#include <msg/messages_size_map.h>
#include <msg/defs/PlatformSetMotorSpeed.h>

Node map[MESSAGES_NUM] = {
    {.id = PLATFORM_SET_MOTOR_SPEED_REQ_ID, .size=sizeof(struct PlatformSetMotorSpeedReq)}
};

uint16_t findSizeForMessageId(uint8_t id)
{
    for (int i = 0 ; i < MESSAGES_NUM; i = i + 1)
    {
        if (map[i].id == id) return map[i].size;
    }
    return 0;
}
