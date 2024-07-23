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

//******************************************************************************
//                   Services Interface
//******************************************************************************
#define PLATFORM_SET_MOTOR_SPEED_REQ_ID       0x01  // -> PlatformSetSpeedReq
#define PLATFORM_SET_MOTOR_SPEED_RESP_ID      0x02  // -> PlatformSetSpeedResp
#define PLATFORM_SET_MOTOR_PWM_VALUE_REQ_ID   0x03  // -> PlatformSetPwmValueReq
#define PLATFORM_SET_MOTOR_PWM_VALUE_RESP_ID  0x04  // -> PlatformSetPwmValueResp
//******************************************************************************


//******************************************************************************
// Fast Response Interface
//******************************************************************************
#define PLATFORM_POLL_STATUS_REQ_ID           0xF1  // -> PlatformPollStatusReq
#define PLATFORM_POLL_STATUS_RESP_ID          0xF2  // -> PlatformPollStatusResp
//******************************************************************************

#endif //MOTORDRIVER_MESSAGE_IDS_H
