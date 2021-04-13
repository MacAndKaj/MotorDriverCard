/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_controller.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_COM_MESSAGE_CONTROL_H
#define MDC_COM_MESSAGE_CONTROL_H

#include <MDC/com/interface/consts.h>

#include <ICI/interthread_com_if_params.h>
#include <MDC/com/interface/defs/Message.h>

#include <stdint.h>

struct MessageControl
{
    uint8_t nextReadMessageId;
    InterThreadComIfParams interThreadComIfParams;
};
typedef struct MessageControl MessageControl;

/// Function validates received frame control data.
/// \param data: const array with size FRAME_CTRL_DATA_SIZE containing {CTRL_DATA|ID}.
/// \return 0 if data correct, 1 otherwise.
int validateCtrlData(MessageControl* messageControl, const uint8_t data[HEADER_SIZE]);

/// Function returns message size in bytes for ID of message.
/// \param data: const array with size HEADER_SIZE containing {CTRL_DATA|ID}.
/// \return size of message in bytes + end byte 0xF0
uint16_t getMessageSize(uint8_t id);

/// Function to serialize message(Response) to byte form to be sent.
/// \param resp
/// \param id
/// \return
char* serialize(void* resp, uint8_t id);

Message* deserialize(char* data, uint8_t id);

void forwardMessage(MessageControl* messageControl, const Message* msg);

#endif //MDC_COM_MESSAGE_CONTROL_H
