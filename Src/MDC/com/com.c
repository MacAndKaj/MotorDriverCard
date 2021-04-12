/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : com.c
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */

#include <MDC/com/com.h>

#include <MDC/com/message_control.h>
#include <MDC/com/interface/consts.h>
#include <MDC/main/log.h>

#include <malloc.h>


/*
 * STRUCTURES FUNCTIONS DECLARATIONS BEGIN
 */
void newRxData(RxBuffer *rxBuffer);

void noNewRxData(RxBuffer *rxBuffer);

void startUartRx(RxBuffer *rxBuffer, uint16_t N);

uint8_t isNewData(RxBuffer *rxBuffer);

enum DataType nextReadType(RxBuffer *rxBuffer);

void setNextMessageId(CommunicationContext *communicationContext, uint8_t newNextReadMessageId);

void setNextReadType(CommunicationContext *communicationContext, enum DataType dataType);

void clearBuffer(RxBuffer *rxBuffer);

enum DataType processFrameCtrlData(CommunicationContext* communicationContext);

void processUserData(CommunicationContext* communicationContext);

/*
 *      STRUCTURES FUNCTIONS DECLARATIONS END
 */

/*
 *  PUBLIC BEGIN
 */

void initCom(CommunicationContext *communicationContext)
{
    communicationContext->rxBuffer.data = NULL;
    communicationContext->rxBuffer.nextRead = FrameCtrlData;

    noNewRxData(&communicationContext->rxBuffer);
    startUartRx(&communicationContext->rxBuffer, HEADER_SIZE);

    communicationContext->msgControl.storage = createMessageStorage();
    communicationContext->msgControl.subscriptionContainer = createSubscriptionContainer();
}

void workCom(CommunicationContext *communicationContext)
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
            printf("Received FrameCtrlData\r\n");
            newNextRead = processFrameCtrlData(communicationContext);
            break;
        }
        case UserData:
        {
            printf("Received UserData\r\n");
            processUserData(communicationContext);
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
        nextReadDataSize = getMessageSize(communicationContext->rxBuffer.data[1]);
    }
    printf("Next read will have %d bytes\r\n", nextReadDataSize);

    clearBuffer(&communicationContext->rxBuffer);
    startUartRx(&communicationContext->rxBuffer, nextReadDataSize);

    //TODO use events from FreeRTOS!!!
    processSubscriptions(&communicationContext->msgControl);
    setNextMessageId(communicationContext, newNextRead);
    setNextReadType(communicationContext, newNextRead);
}

void comReceiveCallback(UART_HandleTypeDef *huart, CommunicationContext *communicationContext)
{
    if (huart->Instance != USART2)
    {
        return;
    }
    newRxData(&communicationContext->rxBuffer);
}

uint16_t subscribe(CommunicationContext* communicationContext, uint8_t id, MessageHandler messageHandler)
{
    return addSubscriptionForMessage(&communicationContext->msgControl, id, messageHandler);
}

void unsubscribe(CommunicationContext* communicationContext, uint16_t subscriptionId)
{
    removeSubscriptionWithId(&communicationContext->msgControl, subscriptionId);
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

void startUartRx(RxBuffer *rxBuffer, uint16_t N)
{
    printf("UART receiving DMA start for %d bytes\n", N);
    rxBuffer->data = (uint8_t *) malloc(N * sizeof(uint8_t));
    HAL_StatusTypeDef status = HAL_UART_Receive_DMA(&huart2, rxBuffer->data, N);

    if (status != HAL_OK)
    {
        printf("UART receiving DMA start failed with status: %d\n", status);
    }
}

void noNewRxData(RxBuffer *rxBuffer)
{
    rxBuffer->newData = 0;
}

uint8_t isNewData(RxBuffer *rxBuffer)
{
    return rxBuffer->newData;
}

enum DataType nextReadType(RxBuffer *rxBuffer)
{
    return rxBuffer->nextRead;
}

void setNextMessageId(CommunicationContext *communicationContext, uint8_t newNextReadMessageId)
{
    communicationContext->msgControl.nextReadMessageId = newNextReadMessageId;
}

void setNextReadType(CommunicationContext *communicationContext, enum DataType dataType)
{
    communicationContext->rxBuffer.nextRead = dataType;
}

void clearBuffer(RxBuffer *rxBuffer)
{
    if (rxBuffer->data == NULL) return;

    free(rxBuffer->data);
    rxBuffer->data = NULL;
    noNewRxData(rxBuffer);
}

enum DataType processFrameCtrlData(CommunicationContext* communicationContext)
{
    int status = validateCtrlData(&communicationContext->msgControl, communicationContext->rxBuffer.data);

    if (status != 0)
    {
        return FrameCtrlData;
    }
    return UserData;
}

void processUserData(CommunicationContext* communicationContext)
{
    struct Message* deserializedMsg = deserialize((char*)communicationContext->rxBuffer.data,
        communicationContext->msgControl.nextReadMessageId);

    if (deserializedMsg == NULL)
    {
        printf("Unknown message\n");
        return;
    }

    addMessage(communicationContext->msgControl.storage, deserializedMsg);
}

/*
 *  PRIVATE END
 */
