/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : rx.c
  * @brief          : Main RxTask file - entry point of task.
  ******************************************************************************
  */

#include <MDC/com/impl/rx.h>

#include <MDC/com/impl/message_control.h>
#include <msg/consts.h>
#include <MDC/main/log.h>

#include <malloc.h>
#include <msg/messages_size_map.h>
#include <MDC/log/interface.h>
#include <MDC/rx/impl/receiver.h>

struct
{
    uint8_t newData;
    uint8_t *data;
    enum DataType nextRead;
} rxBuffer;

void configureRxImpl()
{
    rxBuffer.data = NULL;
    rxBuffer.nextRead = FrameCtrlData;

    startReception(rxBuffer.data, HEADER_SIZE);
}

void clearBuffer(uint16_t nextReadSize)
{
    if (rxBuffer.data == NULL) return;

    free(rxBuffer.data);
    rxBuffer.data = (uint8_t *) malloc(nextReadSize * sizeof(uint8_t));
}

void workCom()
{
    // TODO: wait for new data

    enum DataType newNextRead;
    switch (rxBuffer.nextRead)
    {
        case FrameCtrlData:
        {
            newNextRead = processFrameCtrlData();
            break;
        }
        case UserData:
        {
            processUserData();
            newNextRead = FrameCtrlData;
            break;
        }
        default:
        {
            LOG("Incorrect data type");
            newNextRead = FrameCtrlData;
        }
    }

    uint16_t nextReadDataSize = HEADER_SIZE;
    if (newNextRead == UserData)
    {
        nextReadDataSize = findSizeForMessageId(rxBuffer.data[1]);
    }
//    printf("Next read will have %d bytes\r\n", nextReadDataSize);

    clearBuffer(nextReadDataSize);
    startReception(rxBuffer.data, nextReadDataSize);

    setNextMessageId(newNextRead);
    rxBuffer.nextRead = newNextRead;
}
