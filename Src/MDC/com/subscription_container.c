/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : subscription_container.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/com/subscriptions_container.h>
#include <malloc.h>
#include <stdio.h>

struct Subscription
{
    MessageHandler handlerPtr;
    uint8_t messageId;
    uint16_t subscriptionId;
    struct Subscription* next;
};

struct SubscriptionContainer
{
    struct Subscription* first;
    uint16_t subscriptionsCounter;
};

SubscriptionContainer* createSubscriptionContainer()
{
    struct SubscriptionContainer* ptr = malloc(sizeof(struct SubscriptionContainer));
    ptr->subscriptionsCounter = 0;
    ptr->first = NULL;
    return ptr;
}

uint16_t addSubscription(SubscriptionContainer* container, uint8_t messageId, MessageHandler handler)
{
    struct Subscription** current = &container->first;
    while (*current != NULL)
    {
        current = &(*current)->next;
    }
    printf("Creating subscription for messageId = %d!\r\n", messageId);
    struct Subscription* new = malloc(sizeof(struct Subscription));
    new->next = NULL;
    new->messageId = messageId;
    new->handlerPtr = handler;

    (*current) = new;
    container->subscriptionsCounter = container->subscriptionsCounter + 1;
    return container->subscriptionsCounter - 1;
}

void removeSubscription(SubscriptionContainer* container, uint16_t subscriptionId)
{
    struct Subscription* current = container->first;

    if (current == NULL)
    {
        return;
    }

    while (current->next != NULL && current->next->subscriptionId != subscriptionId)
    {
        current = current->next;
    }

    if (current->next == NULL)
    {
        return;
    }

    struct Subscription* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

int subscriptionExists(SubscriptionContainer* container, uint8_t messageId)
{
    struct Subscription* current = container->first;
    const int SUBSCRIPTION_EXITS = 0;
    const int SUBSCRIPTION_DOES_NOT_EXIST = 1;
    if (current == NULL)
    {
        printf("Subscription for %d does not exist!\r\n", messageId);
        return SUBSCRIPTION_DOES_NOT_EXIST;
    }

    while (current->next != NULL)
    {
        if (current->messageId == messageId)
        {
            return SUBSCRIPTION_EXITS;
        }
    }
    return SUBSCRIPTION_DOES_NOT_EXIST;
}

struct HandlersList getHandlersForMessageId(SubscriptionContainer* container, uint8_t messageId)
{
    struct HandlersList list = {.head=NULL};
    struct HandlerNode** currentHandlerNode = &list.head;
    struct Subscription* currentSubscription = container->first;

    while (currentSubscription != NULL)
    {
        if (currentSubscription->messageId == messageId)
        {
            (*currentHandlerNode) = (struct HandlerNode*)malloc(sizeof(struct HandlerNode));
            (*currentHandlerNode)->messageHandler = currentSubscription->handlerPtr;
            (*currentHandlerNode)->next = NULL;
            currentHandlerNode = &(*currentHandlerNode)->next;
        }
        currentSubscription = currentSubscription->next;
    }

    return list;
}
