/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include "tasks/controller/impl/motor_process.h"
#include "main/defs.h"

#include <stdlib.h>
#include <string.h>
#include <FreeRTOS.h>

void set_left_direction(struct OutputConfiguration* u, Dir direction);
void set_right_direction(struct OutputConfiguration* u, Dir direction);

uint32_t get_pwm_duty(const struct ControlParameters *handle)
{
    return handle->pwmDuty;
}

void set_pwm_duty(struct OutputConfiguration *handle, uint32_t newPwmDuty)
{
    if (newPwmDuty < handle->stopThreshold)
    {
        newPwmDuty = 0;
    }

    if (newPwmDuty > handle->pwmPeriod)
    {
        newPwmDuty = handle->pwmPeriod;
    }
    handle->parameters.pwmDuty = newPwmDuty;
}

void init_pwm(TIM_HandleTypeDef* timer, uint32_t channel, uint32_t* pwmSource)
{
    HAL_StatusTypeDef state = HAL_TIM_PWM_Start_DMA(timer, channel, pwmSource, ONE_WORD);
    if (state != HAL_OK)
    {
        Error_Handler();
    }
}

struct ControlParameters* new_control_parameters()
{
    struct ControlParameters* ret = pvPortMalloc(sizeof(struct ControlParameters));
    memset(ret, 0, sizeof(struct ControlParameters));

    return ret;
}

void motor_process_configure(struct OutputConfiguration* config1, struct OutputConfiguration* config2)
{
    config1->parameters.pwmDuty = 0;
    set_left_direction(config1, Forward);

    config2->parameters.pwmDuty = 0;
    set_right_direction(config2, Forward);

    init_pwm(config1->timer, config1->channel, &config1->parameters.pwmDuty);
    init_pwm(config2->timer, config2->channel, &config2->parameters.pwmDuty);

    HAL_StatusTypeDef state = HAL_TIM_Base_Start_IT(&htim17);
    if (state != HAL_OK)
    {
        Error_Handler();
    }
}

void motor_process_update_u(struct OutputConfiguration* config, int64_t u, bool leftMotor)
{
    if (u < 0 && config->parameters.currentDirection == Forward)
    {
        leftMotor ? set_left_direction(config, BACKWARD) : set_right_direction(config, FORWARD);
    }
    else if (u > 0 && config->parameters.currentDirection == Backward)
    {
        leftMotor ? set_left_direction(config, FORWARD) : set_right_direction(config, BACKWARD);
    }
    set_pwm_duty(config, llabs(u));
}

void set_left_direction(struct OutputConfiguration* u, Dir direction)
{
    uint32_t pwm_duty_temp = get_pwm_duty(&u->parameters);
    set_pwm_duty(u, 0);
    if (direction == Forward)
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_RESET);
    }
    set_pwm_duty(u, pwm_duty_temp);
}

void set_right_direction(struct OutputConfiguration* u, Dir direction)
{
    uint32_t pwm_duty_temp = get_pwm_duty(&u->parameters);
    set_pwm_duty(u, 0);
    if (direction == Forward)
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(u->motorControl1Port, u->motorControl1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(u->motorControl2Port, u->motorControl2Pin, GPIO_PIN_SET);
    }
    set_pwm_duty(u, pwm_duty_temp);
}
