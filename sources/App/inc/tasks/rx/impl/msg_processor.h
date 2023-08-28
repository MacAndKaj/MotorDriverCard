/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : msg_processor.h
  * @brief          : <brief>
  ******************************************************************************
  */

#include <stdint.h>

#ifndef MDC_RX_IMPL_MSG_PROCESSOR_H
#define MDC_RX_IMPL_MSG_PROCESSOR_H


/// Function to serialize message(Response) to byte form to be sent.
/// \param resp
/// \param id
/// \return
char* serialize(void* resp, uint8_t id);

struct Message* processData(const uint8_t* frame_data);

#endif //MDC_RX_IMPL_MSG_PROCESSOR_H
