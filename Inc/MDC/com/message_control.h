/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_controller.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_MESSAGE_CONTROL_H
#define MOTORDRIVER_MESSAGE_CONTROL_H

#include <MDC/com/interface/consts.h>
#include <MDC/com/message_storage.h>
#include <MDC/com/subscriptions_container.h>

#include <stdint.h>

struct MessageControl
{
    uint8_t nextReadMessageId;
    MessageStorage* storage;
    SubscriptionContainer* subscriptionContainer;
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

char* serialize(void* resp, uint8_t id);

Message* deserialize(char* data, uint8_t id);

uint16_t addSubscriptionForMessage(MessageControl* messageControl, uint8_t id,  MessageHandler messageHandler);
void removeSubscriptionWithId(MessageControl* messageControl, uint16_t subscriptionId);

void processSubscriptions(MessageControl* messageControl);

#endif //MOTORDRIVER_MESSAGE_CONTROL_H
