/**
  * Copyright (c) 2026 MacAndKaj. All rights reserved.
  *
  ******************************************************************************
  * @file           : scan.c
  * @brief          : Implementation of scan module
  ******************************************************************************
  */
#include <modules/scan/impl/scan.h>

#include <main/defs.h>
#include "modules/log/interface.h"

#include "FreeRTOSConfig.h"
#include "main.h"
#include "projdefs.h"
#include "portmacro.h"

// void trigger_distance_sensors(struct scan_data *data);

void scan_init(struct scan_data *data)
{
    // Initialize scan module
    if (data->start_pwm != NULL)
    {
        data->internal_data->up_counting = true;  // Start with counting up
        data->internal_data->pwm_scan_servo = 500;  // Set initial PWM value for servo
        data->start_pwm(&data->internal_data->pwm_scan_servo);  // Start PWM on TIM15
        osDelay(pdMS_TO_TICKS(1000));
    }
    LOG_INFO("[scan] Initialized\n");
}

void scan_work(struct scan_data *data)
{
    // Main work loop for scan
    // Add scanning logic here
    struct scan_internal_data *internal_data = data->internal_data;
    osDelay(pdMS_TO_TICKS(1000));  // Example delay
    if (internal_data->up_counting && internal_data->pwm_scan_servo == 2500)
    {
        internal_data->up_counting = false;  // Switch to counting down
    }
    else if (!internal_data->up_counting && internal_data->pwm_scan_servo == 500)
    {
        internal_data->up_counting = true;  // Switch to counting up
    }


    internal_data->pwm_scan_servo += internal_data->up_counting ? 100 : -100;
    osDelay(pdMS_TO_TICKS(10));  // Example delay
    // trigger_distance_sensors(data);
}

