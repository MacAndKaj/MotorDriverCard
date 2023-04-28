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

/// Startup function to initialize msgProcessor
void configureMsgProcessor();

/// Returns next data type expected on Rx line.
enum DataType getNextDataType();
uint16_t getNextMessageSize();

/// Function to serialize message(Response) to byte form to be sent.
/// \param resp
/// \param id
/// \return
char* serialize(void* resp, uint8_t id);

struct Message* deserialize(char* data, uint8_t id);

enum DataType processFrameCtrlData(const uint8_t* data);

struct Message* processUserData(uint8_t* data);

#endif //MDC_RX_IMPL_MSG_PROCESSOR_H
