/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : PlatformPollStatus.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_MSG_DEFS_PLATFORMPOLLSTATUS_H
#define MDC_MSG_DEFS_PLATFORMPOLLSTATUS_H

#include "msg/consts.h"

#include <stdint.h>

/*
 * statusSet - bitset to request specific statuses
 *      bits:
 *           0 - speed
 *           1 - modules status
 */
struct PlatformPollStatusReq
{
    uint8_t statusSet; 
};
typedef struct PlatformPollStatusReq PlatformPollStatusReq;

/*
 * lSpeedF/rSpeedF  - fraction part of speed values - 0.xx
 * lSpeedI/rSpeedI  - integer part of speed values - xxx.0
 * moduleStatus     - bitset with modules Status (1-OK, 0-NOK)
 *                  bits: 0...7 - controller|feedback|log|syscom|[4...7 Not used]
 */
struct PlatformPollStatusResp
{
    int8_t lSpeedI;
    uint8_t lSpeedF; 
    int8_t rSpeedI;
    uint8_t rSpeedF;
    uint8_t moduleStatus;
};
typedef struct PlatformPollStatusResp PlatformPollStatusResp;

#endif //MDC_MSG_DEFS_PLATFORMPOLLSTATUS_H
