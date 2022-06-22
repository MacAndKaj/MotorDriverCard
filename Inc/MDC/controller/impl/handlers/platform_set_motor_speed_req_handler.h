/**
  ******************************************************************************
  * @file           : platform_set_motor_speed_req_handler.h
  * @brief          : Header for platform_set_motor_speed_req_handler.c file.
  ******************************************************************************
  */
#ifndef MDC_CONTROLLER_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H
#define MDC_CONTROLLER_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H

#include <msg/defs/PlatformSetMotorSpeed.h>

void platform_set_motor_speed_req_handler_configure(double *destLSpeed, double *destRSpeed);
void platform_set_motor_speed_req_handler_handle(const PlatformSetMotorSpeedReq* msg);

#endif //MDC_CONTROLLER_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H