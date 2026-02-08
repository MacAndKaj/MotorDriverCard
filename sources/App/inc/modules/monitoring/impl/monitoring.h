/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : monitoring.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_MONITORING_IMPL_MONITORING_H
#define MDC_MONITORING_IMPL_MONITORING_H

#include <modules/monitoring/interface.h>

void monitoring_init(struct monitoring_data *handle);
void monitoring_work(struct monitoring_data *handle);

#endif // MDC_MONITORING_IMPL_MONITORING_H
