/**
  ******************************************************************************
  * @file           : platform_set_motor_pwm_value_req_handler.h
  * @brief          : Header for platform_set_motor_pwm_value_req_handler.c file.
  ******************************************************************************
  */
#ifndef MDC_MODULES_CONTROLLER_IMPL_HANDLERS_PLATFORM_SET_MOTOR_PWM_VALUE_REQ_HANDLER_H
#define MDC_MODULES_CONTROLLER_IMPL_HANDLERS_PLATFORM_SET_MOTOR_PWM_VALUE_REQ_HANDLER_H

#include <modules/controller/impl/controller.h>
#include <msg/defs/PlatformSetMotorPwmValue.h>

typedef void (*platform_set_motor_pwm_value_req_callback)(struct controller_internal_data *, int, int);
/**
 * @brief Configure handler for new motor PWM value.
 *
 * @param cb Callback to function handling new speed to set (int left_pwm, int right_pwm)
 */
void platform_set_motor_pwm_value_req_handler_configure(struct controller_internal_data *h, platform_set_motor_pwm_value_req_callback cb);

/**
 * @brief Handle new message with motors PWM value. Should be used only by message dispatcher.
 *
 * @param msg Received message with new motors PWM value.
 */
void platform_set_motor_pwm_value_req_handler_handle(const PlatformSetMotorPwmValueReq *msg);

#endif //MDC_MODULES_CONTROLLER_IMPL_HANDLERS_PLATFORM_SET_MOTOR_PWM_VALUE_REQ_HANDLER_H