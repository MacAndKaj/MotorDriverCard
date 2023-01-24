/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : init_interrupt_service.c
  * @brief          : Sources for init.h file.
  *                   This file contains definitions of init functions.
  ******************************************************************************
  */

#include <MDC/main/services/interrupt_service.h>
#include <stddef.h>

#define MAX_HANDLERS 100

struct HandlersListItem
{
    uint16_t gpioPin;

    void (*callback)(void);
};

struct InterruptService
{
    struct HandlersListItem handlers[MAX_HANDLERS];
    uint8_t handlersSize;
};

static struct InterruptService service;

void dispatch_interrupt(uint16_t GPIO_Pin)
{
    for (int i = 0; i < service.handlersSize; i++)
    {
        if (service.handlers[i].gpioPin == GPIO_Pin)
        {
            service.handlers[i].callback();
        }
    }
}

int subscribeForInterrupt(uint16_t GPIO_Pin, void (*handler)(void))
{
    if (service.handlersSize == MAX_HANDLERS)
    {
        return -1;
    }

    service.handlers[service.handlersSize].callback = handler;
    service.handlers[service.handlersSize].gpioPin = GPIO_Pin;

    return service.handlersSize;
}

struct InterruptServiceInterface init_interrupt_service()
{
    struct InterruptServiceInterface temp;

    service.handlersSize = 0;
    for (int i = 0; i < MAX_HANDLERS; ++i)
    {
        service.handlers->callback = NULL;
        service.handlers->gpioPin = 0;
    }
    temp.subscribeForInterrupt = subscribeForInterrupt;
    return temp;
}


