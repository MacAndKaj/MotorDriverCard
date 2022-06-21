/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <MDC/main/init.h>

#include <msg/defs/Message.h>
#include <log/interface.h>
#include <MDC/rx/interface.h>
#include "MDC/platform/platform.h"

#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for motorCtrlTask */
osThreadId_t motorCtrlTaskHandle;
const osThreadAttr_t motorCtrlTask_attributes = {
  .name = "motorCtrlTask",
  .stack_size = 200 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for rxTask */
osThreadId_t rxTaskHandle;
const osThreadAttr_t rxTask_attributes = {
  .name = "rxTask",
  .stack_size = 200 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for messagesQueue */
osMessageQueueId_t messagesQueueHandle;
const osMessageQueueAttr_t messagesQueue_attributes = {
  .name = "messagesQueue"
};
/* Definitions for messageReceived */
osEventFlagsId_t messageReceivedHandle;
const osEventFlagsAttr_t messageReceived_attributes = {
  .name = "messageReceived"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void startMotorControlTask(void *argument);
void startCommunicationTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    if (mainInit() != 0)
    {
        return;
    }

    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    HAL_Delay(300);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of messagesQueue */
  messagesQueueHandle = osMessageQueueNew (3, sizeof(Message), &messagesQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of motorCtrlTask */
  motorCtrlTaskHandle = osThreadNew(startMotorControlTask, NULL, &motorCtrlTask_attributes);

  /* creation of rxTask */
  rxTaskHandle = osThreadNew(startCommunicationTask, NULL, &rxTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of messageReceived */
  messageReceivedHandle = osEventFlagsNew(&messageReceived_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
    configureRx(&rxTaskHandle, &messagesQueueHandle);
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_startMotorControlTask */
/**
  * @brief  Function implementing the motorCtrlTask thread.
  * @param  argument: Not used
  * @retval None
  */
_Noreturn
/* USER CODE END Header_startMotorControlTask */
void startMotorControlTask(void *argument)
{
  /* USER CODE BEGIN startMotorControlTask */
    LOG_INFO("Start motor control\n");
  /* Infinite loop */
  for(;;)
  {
      workPlatform(&messagesQueueHandle);
      osThreadYield();
  }
  /* USER CODE END startMotorControlTask */
}

/* USER CODE BEGIN Header_startCommunicationTask */
/**
* @brief Function implementing the comTask thread.
* @param argument: Not used
* @retval None
*/
_Noreturn
/* USER CODE END Header_startCommunicationTask */
void startCommunicationTask(void *argument)
{
  /* USER CODE BEGIN startCommunicationTask */
    LOG_INFO("Start Rx\n");
  /* Infinite loop */
  for(;;)
  {
      workRx();
  }
  /* USER CODE END startCommunicationTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
