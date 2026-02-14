/**
* Copyright (c) 2026 MacAndKaj. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformStatus.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_MSG_DEFS_PLATFORMSTATUS_H
#define MDC_MSG_DEFS_PLATFORMSTATUS_H

#include "msg/consts.h"

#include <stdint.h>

/*
 * lSpeedF/rSpeedF  - fraction part of speed values - 0.xx
 * lSpeedI/rSpeedI  - integer part of speed values - xxx.0
 * system_state     - bitset with modules Status (1-OK, 0-NOK)
 *                  bits: 0...7 - controller|feedback|log|syscom|[4...7 Not used]
 * fault_flags
 */
typedef struct
{
    int8_t l_speed_i;
    uint8_t l_speed_f;
    int8_t r_speed_i;
    uint8_t r_speed_f;
    uint16_t system_state;   // bitmask
    uint16_t fault_flags;

    uint16_t  last_cmd_seq_id;
    uint8_t  last_cmd_status; // CommandStatus
    uint8_t  reserved;
} PlatformStatus;

#endif // MDC_MSG_DEFS_PLATFORMSTATUS_H
