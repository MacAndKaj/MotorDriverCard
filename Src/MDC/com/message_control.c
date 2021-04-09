/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : message_control.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/com/message_control.h>

#include <MDC/com/interface/consts.h>
#include <MDC/com/interface/messages_size_map.h>
#include <MDC/com/interface/ser_des/deserializers/PlatformSetMotorSpeed.h>
#include <MDC/com/interface/ser_des/serializers/PlatformSetMotorSpeed.h>

#include <stddef.h>
#include <malloc.h>

int validateCtrlData(MessageControl* messageControl, const uint8_t data[HEADER_SIZE])
{
    if (data[0] != FRAME_CTRL_DATA) return 1;

    return 0;
}

uint16_t getMessageSize(uint8_t id)
{
    Node* idAndSize = findSizeForMessageId(id);
    if (idAndSize != NULL)
    {
        return idAndSize->size;
    }
    return 0;
}

char* serialize(void* resp, uint8_t id)
{
    switch (id)
    {
        case PLATFORM_SET_MOTOR_SPEED_RESP_ID:
            return serialize_PlatformSetMotorSpeedResp((PlatformSetMotorSpeedResp*) resp);
    }
    return NULL;
}

Message* deserialize(char* data, uint8_t id)
{
    struct Message* message = malloc(sizeof(struct Message));
    message->messageId=id;
    switch (id)
    {
        case PLATFORM_SET_MOTOR_SPEED_REQ_ID:
            message->msg.platformSetMotorSpeedReq = *deserialize_PlatformSetMotorSpeedReq(data);
            return message;
        default:
            free(message);
    }
    return NULL;
}

uint16_t addSubscriptionForMessage(MessageControl* messageControl, uint8_t id, MessageHandler messageHandler)
{
    if (findSizeForMessageId(id) == NULL)
    {
        return -1;
    }

    return addSubscription(messageControl->subscriptionContainer, id, messageHandler);
}

void removeSubscriptionWithId(MessageControl* messageControl, uint16_t subscriptionId)
{
    removeSubscription(messageControl->subscriptionContainer, subscriptionId);
}

void processSubscriptions(MessageControl* messageControl)
{
    struct HandlersList handlersList;
    while (!isEmpty(messageControl->storage))
    {
        Message message = popMessage(messageControl->storage);
        if (subscriptionExists(messageControl->subscriptionContainer, message.messageId))
        {
            handlersList = getHandlersForMessageId(messageControl->subscriptionContainer, message.messageId);
            struct HandlerNode* current = handlersList.head;

            while (current != NULL)
            {
                current->messageHandler(&message);
                current = current->next;
            }
        }
    }

}
