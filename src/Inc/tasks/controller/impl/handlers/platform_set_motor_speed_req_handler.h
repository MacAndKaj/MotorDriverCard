/**
  ******************************************************************************
  * @file           : platform_set_motor_speed_req_handler.h
  * @brief          : Header for platform_set_motor_speed_req_handler.c file.
  ******************************************************************************
  */
#ifndef MDC_CONTROLLER_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H
#define MDC_CONTROLLER_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H

#include <msg/defs/PlatformSetMotorSpeed.h>

/**
 * @brief Configure handler for new motor speed.
 * 
 * @param cb Callback to function handling new speed to set (double leftSpeed, double rightSpeed)
 */
void platform_set_motor_speed_req_handler_configure(void (*cb)(double, double));

/**
 * @brief Handle new message with motors speed. Should be used only by message dispatcher.
 * 
 * @param msg Received message with new motors speed.
 */
void platform_set_motor_speed_req_handler_handle(const PlatformSetMotorSpeedReq* msg);

#endif //MDC_CONTROLLER_IMPL_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H