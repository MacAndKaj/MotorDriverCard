/**
  * Copyright (c) 2026 MacAndKaj. All rights reserved.
  *
  ******************************************************************************
  * @file           : scan.h
  * @brief          : Internal header for scan module
  ******************************************************************************
  */
#ifndef MDC_MODULES_SCAN_IMPL_SCAN_H
#define MDC_MODULES_SCAN_IMPL_SCAN_H

#include <stdbool.h>
#include <modules/scan/interface.h>

struct scan_internal_data
{
    uint16_t pwm_scan_servo;
    bool up_counting;
};

void scan_init(struct scan_data *data);
void scan_work(struct scan_data *data);

#endif //MDC_MODULES_SCAN_IMPL_SCAN_H
