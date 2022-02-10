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

#include <gpio.h>
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

void initPwm(TIM_HandleTypeDef* timer, uint32_t channel, uint32_t* pwmSource)
{
    HAL_StatusTypeDef state = HAL_TIM_PWM_Start_DMA(timer, channel, pwmSource, ONE_WORD);
    if (state != HAL_OK)
    {
        Error_Handler();
    }
}

void configureMotorProcess(struct OutputConfiguration* config1, struct OutputConfiguration* config2)
{
    initPwm(config1->timer, config1->channel, &config1->parameters->pwmDuty);
    initPwm(config2->timer, config2->channel, &config2->parameters->pwmDuty);

    HAL_StatusTypeDef state = HAL_TIM_Base_Start_IT(&htim17);
    if (state != HAL_OK)
    {
        Error_Handler();
    }
}

void updateU(struct OutputConfiguration* config, int64_t newPwmDuty, bool leftMotor)
{
    if (newPwmDuty < 0 && config->parameters->currentDirection == Forward)
    {
        leftMotor ? setLeftDirection(config, BACKWARD) : setRightDirection(config, FORWARD);
    }
    else if (newPwmDuty > 0 && config->parameters->currentDirection == Backward)
    {
        leftMotor ? setLeftDirection(config, FORWARD) : setRightDirection(config, BACKWARD);
    }
    setPwmDuty(config->parameters, llabs(newPwmDuty));
}

void setPwmDuty(struct ControlParameters *handle, uint32_t newPwmDuty)
{
    if (newPwmDuty < STOP_THRESHOLD)
    {
        newPwmDuty = 0;
    }

    if (newPwmDuty > PWM_PERIOD)
    {
        newPwmDuty = PWM_PERIOD;
    }
    handle->pwmDuty = newPwmDuty;
}

void setLeftDirection(struct OutputConfiguration* u, Dir direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(u->parameters);
    setPwmDuty(u->parameters, 0);
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
    setPwmDuty(u->parameters, pwm_duty_temp);
}

void setRightDirection(struct OutputConfiguration* u, Dir direction)
{
    uint32_t pwm_duty_temp = getPwmDuty(u->parameters);
    setPwmDuty(u->parameters, 0);
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
    setPwmDuty(u->parameters, pwm_duty_temp);
}
