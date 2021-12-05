/**
  * Copyright (c) 2021 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : receiver.c
  * @brief          : <brief>
  ******************************************************************************
  */


void startReception(uint8_t* dest, uint16_t N)
{
//    printf("UART receiving DMA start for %d bytes\n", N);
    HAL_StatusTypeDef status = HAL_UART_Receive_DMA(&huart2, dest, N);

    if (status != HAL_OK)
    {
        LOG("ERROR when receiving from UART2");
    }
}
