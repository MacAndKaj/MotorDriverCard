/**
  ******************************************************************************
  * @file           : platform_set_motor_speed_req_handler.h
  * @brief          : Header for platform_set_motor_speed_req_handler.c file.
  ******************************************************************************
  */
#ifndef MDC_MODULES_CONTROLLER_IMPL_HANDLERS_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H
#define MDC_MODULES_CONTROLLER_IMPL_HANDLERS_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H

#include <modules/controller/impl/controller.h>
#include <msg/defs/PlatformSetMotorSpeed.h>

typedef void (*platform_set_motor_speed_req_callback)(struct controller_internal_data *, double, double);
/**
 * @brief Configure handler for new motor speed.
 * 
 * @param cb Callback to function handling new speed to set (double leftSpeed, double rightSpeed)
 */
void platform_set_motor_speed_req_handler_configure(struct controller_internal_data *h, platform_set_motor_speed_req_callback cb);

/**
 * @brief Handle new message with motors speed. Should be used only by message dispatcher.
 * 
 * @param msg Received message with new motors speed.
 */
void platform_set_motor_speed_req_handler_handle(const PlatformSetMotorSpeedReq* msg);

#endif //MDC_MODULES_CONTROLLER_IMPL_HANDLERS_PLATFORM_SET_MOTOR_SPEED_REQ_HANDLER_H