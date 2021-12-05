/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : msg_processor.h
  * @brief          : <brief>
  ******************************************************************************
  */

#ifndef MDC_RX_IMPL_MSG_PROCESSOR_H
#define MDC_RX_IMPL_MSG_PROCESSOR_H

/// Function validates received frame control data.
/// \param data: const array with size FRAME_CTRL_DATA_SIZE containing {CTRL_DATA|ID}.
/// \return 0 if data correct, 1 otherwise.
int validateCtrlData(MessageControl* messageControl, const uint8_t data[HEADER_SIZE]);

/// Function to serialize message(Response) to byte form to be sent.
/// \param resp
/// \param id
/// \return
char* serialize(void* resp, uint8_t id);

Message* deserialize(char* data, uint8_t id);

#endif //MDC_RX_IMPL_MSG_PROCESSOR_H
