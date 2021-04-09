/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : subscriptions_container.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_INC_COM_SUBSCRIPTIONS_CONTAINER_H
#define MOTORDRIVER_INC_COM_SUBSCRIPTIONS_CONTAINER_H

#include <MDC/com/interface/defs/Message.h>

typedef void(*MessageHandler)(Message*);

struct HandlerNode
{
    MessageHandler messageHandler;
    struct HandlerNode* next;
};

struct HandlersList
{
    struct HandlerNode* head;
};

struct SubscriptionContainer;
typedef struct SubscriptionContainer SubscriptionContainer;

/// Creates empty SubscriptionContainer.
/// \return Pointer to SubscriptionContainer.
SubscriptionContainer* createSubscriptionContainer();

/// Adds subscription to SubscriptionContainer.
/// \param container[in|out]: Pointer to SubscriptionContainer.
/// \param messageId[in]: ID of message to subscribe for.
/// \param handler[in]: Pointer to function handling message.
/// \return: Subscription ID.
uint16_t addSubscription(SubscriptionContainer* container, uint8_t messageId, MessageHandler handler);

/// Function checks if subscription for specific message ID exists in SubscriptionContainer.
/// \param container[in|out]: Pointer to SubscriptionContainer.
/// \param messageId[in]: ID of message that subscription is checked.
/// \return: 0 if subscription exists, 1 otherwise.
int subscriptionExists(SubscriptionContainer* container, uint8_t messageId);

/// Returns list of MessageHandlers for specified message ID.
/// \param container[in]: Pointer to SubscriptionContainer.
/// \param messageId[in]: Message ID that that handlers are needed.
/// \return List of handlers.
struct HandlersList getHandlersForMessageId(SubscriptionContainer* container, uint8_t messageId);

/// Removes subscription from SubscriptionContainer.
/// \param container[in|out]: Pointer to SubscriptionContainer.
/// \param subscriptionId[in]: ID of subscription to be removed.
void removeSubscription(SubscriptionContainer* container, uint16_t subscriptionId);

#endif //MOTORDRIVER_INC_COM_SUBSCRIPTIONS_CONTAINER_H
