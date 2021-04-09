/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_storage.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_INC_COM_MESSAGE_STORAGE_H
#define MOTORDRIVER_INC_COM_MESSAGE_STORAGE_H

#include <MDC/com/interface/defs/Message.h>

struct MessageStorage;
typedef struct MessageStorage MessageStorage;

/// Creates MessageStorage object.
/// \return Pointer to MessageStorage.
MessageStorage* createMessageStorage();

/// Adds message to MessageStorage.
/// \param messageStorage[in|out]: MessageStorage that Message has to be added to.
/// \param msg[in]: Message to be added to MessageStorage.
void addMessage(MessageStorage* messageStorage, const Message* msg);

/// Checks if any message is present in storage.
/// \param messageStorage[in]: MessageStorage to be checked.
/// \return 0 if MessageStorage is empty, 1 otherwise.
int isEmpty(const MessageStorage* messageStorage);

/// Returns first Message from container and removes reference from it.
/// \param messageStorage[in|out]: MessageStorage that Message has to be taken from.
/// \return Message from Container, Undefined if storage is empty.
Message popMessage(MessageStorage* messageStorage);

#endif //MOTORDRIVER_INC_COM_MESSAGE_STORAGE_H
