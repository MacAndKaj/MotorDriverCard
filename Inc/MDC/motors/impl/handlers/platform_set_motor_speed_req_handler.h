/**
  ******************************************************************************
  * @file           : platform_set_motor_speed_req_handler.h
  * @brief          : Header for platform_set_motor_speed_req_handler.c file.
  ******************************************************************************
  */
#ifndef MDC_MOTORS_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H
#define MDC_MOTORS_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H

#include <msg/defs/PlatformSetMotorSpeed.h>

void handlePlatformSetMotorSpeedReq(const PlatformSetMotorSpeedReq* msg);

#endif //MDC_MOTORS_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H