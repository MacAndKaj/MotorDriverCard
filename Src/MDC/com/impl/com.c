/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : com.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/com/impl/rx.h>

#include <MDC/com/impl/message_control.h>
#include <msg/consts.h>
#include <MDC/main/log.h>

#include <malloc.h>
#include <msg/messages_size_map.h>
#include <MDC/log/interface.h>

CommunicationContext* communicationContext;

/*
 * STRUCTURES FUNCTIONS DECLARATIONS BEGIN
 */
void newRxData(RxBuffer *rxBuffer);

void noNewRxData(RxBuffer *rxBuffer);

void startUartRx(RxBuffer *rxBuffer, uint16_t N);

uint8_t isNewData(RxBuffer *rxBuffer);

enum DataType nextReadType(RxBuffer *rxBuffer);

void setNextMessageId(uint8_t newNextReadMessageId);

void setNextReadType(enum DataType dataType);

void clearBuffer(RxBuffer *rxBuffer);

enum DataType processFrameCtrlData();

void processUserData();

/*
 *      STRUCTURES FUNCTIONS DECLARATIONS END
 */

/*
 *  PUBLIC BEGIN
 */

CommunicationContext* createCommunicationContext()
{
    CommunicationContext* contextPtr = malloc(sizeof(CommunicationContext));

    contextPtr->rxBuffer.data = NULL;
    contextPtr->rxBuffer.nextRead = FrameCtrlData;

    return contextPtr;
}

void configureComImpl()
{
    communicationContext = createCommunicationContext();

    noNewRxData(&communicationContext->rxBuffer);
    startUartRx(&communicationContext->rxBuffer, HEADER_SIZE);
}

void workCom()
{
    if (!isNewData(&communicationContext->rxBuffer))
    {
        return;
    }

    enum DataType newNextRead;
    switch (nextReadType(&communicationContext->rxBuffer))
    {
        case FrameCtrlData:
        {
            LOG("Received FrameCtrlData\r\n");
            newNextRead = processFrameCtrlData();
            break;
        }
        case UserData:
        {
            LOG("Received UserData\r\n");
            processUserData();
            newNextRead = FrameCtrlData;
            break;
        }
        default:
        {
            printf("Incorrect data type: %d\n", nextReadType(&communicationContext->rxBuffer));
            newNextRead = FrameCtrlData;
        }
    }

    uint16_t nextReadDataSize = HEADER_SIZE;
    if (newNextRead == UserData)
    {
        nextReadDataSize = findSizeForMessageId(communicationContext->rxBuffer.data[1]);
    }
    printf("Next read will have %d bytes\r\n", nextReadDataSize);

    clearBuffer(&communicationContext->rxBuffer);
    startUartRx(&communicationContext->rxBuffer, nextReadDataSize);

    setNextMessageId(newNextRead);
    setNextReadType(newNextRead);
}

void comReceiveCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance != USART2)
    {
        return;
    }
    newRxData(&communicationContext->rxBuffer);
}

/*
 *  PUBLIC END
 */


/*
 *  PRIVATE BEGIN
 */

void newRxData(RxBuffer *rxBuffer)
{
    rxBuffer->newData = 1;
}

void setNextMessageId(uint8_t newNextReadMessageId)
{
    communicationContext->msgControl.nextReadMessageId = newNextReadMessageId;
}


enum DataType processFrameCtrlData()
{
    int status = validateCtrlData(&communicationContext->msgControl, communicationContext->rxBuffer.data);

    if (status != 0)
    {
        return FrameCtrlData;
    }
    return UserData;
}

void processUserData()
{
    struct Message* deserializedMsg = deserialize((char*)communicationContext->rxBuffer.data,
        communicationContext->msgControl.nextReadMessageId);

    if (deserializedMsg == NULL)
    {
        printf("Unknown message\n");
        return;
    }

    forwardMessage(&communicationContext->msgControl, deserializedMsg);
}

/*
 *  PRIVATE END
 */
