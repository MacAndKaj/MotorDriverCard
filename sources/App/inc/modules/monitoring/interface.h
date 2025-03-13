/**
  * Copyright (c) 2025 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : interface.h
  * @brief          : <brief>
  ******************************************************************************
  */
 #ifndef MDC_MODULES_MONITORING_INTERFACE_H
 #define MDC_MODULES_MONITORING_INTERFACE_H
 
 #include <cmsis_os2.h>
 #include <main/defs.h>
 
 struct module;
 struct monitoring_internal_data;
 
 struct monitoring_data
 {
     osMessageQueueId_t  *syscom_message_queue_handle;
     osMessageQueueId_t  *internal_message_queue_handle;
     send_syscom_message_func_t send_syscom_message;
     struct monitoring_internal_data *internal_data;
 };
 
 void monitoring_module_init(struct module *this_module);
 
 #endif //MDC_MODULES_MONITORING_INTERFACE_H
 