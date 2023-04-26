/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_ids.h
  * @brief          : Header without sources.
  *                   This file contains message ids.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_MESSAGE_IDS_H
#define MOTORDRIVER_MESSAGE_IDS_H

#define PLATFORM_SET_MOTOR_SPEED_REQ_ID 0x01  // -> PlatformSetSpeedReq
#define PLATFORM_SET_MOTOR_SPEED_RESP_ID 0x02  // -> PlatformSetSpeedResp

#define MESSAGES_NUM 1  // Number of IF messages that can be sent to motors

#endif //MOTORDRIVER_MESSAGE_IDS_H
