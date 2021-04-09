/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_storage.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/com/message_storage.h>
#include <stddef.h>
#include <malloc.h>
#include <stdio.h>

struct MessageBox
{
    Message message;
    struct MessageBox* next;
};

struct MessageStorage
{
    struct MessageBox *firstMessage;
};

MessageStorage* createMessageStorage()
{
    struct MessageStorage* ptr = malloc(sizeof(struct MessageStorage));
    ptr->firstMessage = NULL;
    return ptr;
}

void addMessage(MessageStorage* messageStorage, const Message* msg)
{
    struct MessageBox** current = &messageStorage->firstMessage;
    while (*current != NULL)
    {
        current = &(*current)->next;
    }
    struct MessageBox* new = malloc(sizeof(struct MessageBox));
    new->message = *msg;
    new->next = NULL;
    (*current) = new;
    printf("Added message with id %d\r\n", msg->messageId);
}

Message popMessage(MessageStorage* messageStorage)
{
    Message temp = {};
    if (messageStorage->firstMessage == NULL)
    {
        return temp;
    }

    struct MessageBox* second = messageStorage->firstMessage->next;
    temp = messageStorage->firstMessage->message;
    free(messageStorage->firstMessage);

    messageStorage->firstMessage = second;

    return temp;
}

int isEmpty(const MessageStorage* messageStorage)
{
    return messageStorage->firstMessage == NULL;
}
