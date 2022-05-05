/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : controller.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/motors/impl/motor_process.h>
#include <MDC/main/defs.h>

#include <tim.h>

#include <stdlib.h>

typedef enum {
    Forward,
    Backward
} Dir;

struct ControlParameters
{
    uint32_t pwmDuty;
    Dir currentDirection;
};

void setLeftDirection(struct OutputConfiguration* u, Dir direction);
void setRightDirection(struct OutputConfiguration* u, Dir direction);

uint32_t getPwmDuty(const struct ControlParameters *handle)
{
    return handle->pwmDuty;
}

void setPwmDuty(struct OutputConfiguration *handle, uint32_t newPwmDuty)
{
    if (newPwmDuty < handle->stopThreshold)
    {
        newPwmDuty = 0;
    }

    if (newPwmDuty > handle->pwmPeriod)
    {
        newPwmDuty = handle->pwmPeriod;
    }
    handle->parameters->pwmDuty = newPwmDuty;
}

void initPwm(TIM_HandleTypeDef* timer, uint32_t channel, uint32_t* pwmSource)
{
    HAL_StatusTypeDef state = HAL_TIM_PWM_Start_DMA(timer, channel, pwmSource, ONE_WORD);
    if (state != HAL_OK)
    {
        Error_Handler();
    }
}

void motor_process_configure(struct OutputConfiguration* config1, struct OutputConfiguration* config2)
{
    config1->parameters = malloc(sizeof(struct ControlParameters));
    config1->parameters->pwmDuty = 0;
    setLeftDirection(config1, Forward);

    config2->parameters = malloc(sizeof(struct ControlParameters));
    config2->parameters->pwmDuty = 0;
    setRightDirection(config2, Forward);

    initPwm(config1->timer, config1->channel, &config1->parameters->pwmDuty);
    initPwm(config2->timer, config2->channel, &config2->parameters->pwmDuty);

    HAL_StatusTypeDef state = HAL_TIM_Base_Start_IT(&htim17);
    if (state != HAL_OK)
    {
        Error_Handler();
    }
}

void motor_process_updateU(struct OutputConfiguration* config, int64_t u, bool leftMotor)
{
    if (u < 0 && config->parameters->currentDirection == Forward)
    {
        leftMotor ? setLeftDirection(config, BACKWARD) : setRightDirection(config, FORWARD);
    }
    else if (u > 0 && config->parameters->currentDirection == Backward)
    {
        leftMotor ? setLeftDirection(config, FORWARD) : setRightDirection(config, BACKWARD);
    }
    setPwmDuty(config, llabs(u));
}

void setLeftDirection(struct OutputConfiguration* u, Dir direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(u->parameters);
    setPwmDuty(u, 0);
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
    setPwmDuty(u, pwm_duty_temp);
}

void setRightDirection(struct OutputConfiguration* u, Dir direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(u->parameters);
    setPwmDuty(u, 0);
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
    setPwmDuty(u, pwm_duty_temp);
}
