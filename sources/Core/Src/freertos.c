/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include <log/interface.h>
#include <main/context.h>
#include <main/defs.h>
#include <msg/defs/Message.h> // Change to lowercase
#include <tasks/controller/interface.h>
#include <tasks/feedback/interface.h>
#include <tasks/rx/interface.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
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
/* Definitions for controllerTask */
osThreadId_t controllerTaskHandle;
const osThreadAttr_t controllerTask_attributes = {
  .name = "controllerTask",
  .stack_size = 320 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for feedbackTask */
osThreadId_t feedbackTaskHandle;
const osThreadAttr_t feedbackTask_attributes = {
  .name = "feedbackTask",
  .stack_size = 320 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for rxTask */
osThreadId_t rxTaskHandle;
const osThreadAttr_t rxTask_attributes = {
  .name = "rxTask",
  .stack_size = 320 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for messagesQueue */
osMessageQueueId_t messagesQueueHandle;
uint8_t messagesQueueBuffer[ 2 * sizeof( struct Message ) ];
osStaticMessageQDef_t messagesQueueControlBlock;
const osMessageQueueAttr_t messagesQueue_attributes = {
  .name = "messagesQueue",
  .cb_mem = &messagesQueueControlBlock,
  .cb_size = sizeof(messagesQueueControlBlock),
  .mq_mem = &messagesQueueBuffer,
  .mq_size = sizeof(messagesQueueBuffer)
};
/* Definitions for speedMeasQueue */
osMessageQueueId_t speedMeasQueueHandle;
uint8_t speedMeasQueueBuffer[ 1 * sizeof( struct SpeedValues ) ];
osStaticMessageQDef_t speedMeasQueueControlBlock;
const osMessageQueueAttr_t speedMeasQueue_attributes = {
  .name = "speedMeasQueue",
  .cb_mem = &speedMeasQueueControlBlock,
  .cb_size = sizeof(speedMeasQueueControlBlock),
  .mq_mem = &speedMeasQueueBuffer,
  .mq_size = sizeof(speedMeasQueueBuffer)
};
/* Definitions for logMutex */
osMutexId_t logMutexHandle;
osStaticMutexDef_t logMutexControlBlock;
const osMutexAttr_t logMutex_attributes = {
  .name = "logMutex",
  .cb_mem = &logMutexControlBlock,
  .cb_size = sizeof(logMutexControlBlock),
};
/* Definitions for messageReceived */
osEventFlagsId_t messageReceivedHandle;
const osEventFlagsAttr_t messageReceived_attributes = {
  .name = "messageReceived"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void startController(void *argument);
void startFeedbackTask(void *argument);
void startRxTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    HAL_Delay(300);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of logMutex */
  logMutexHandle = osMutexNew(&logMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
    configure_log(&logMutexHandle);

  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of messagesQueue */
  messagesQueueHandle = osMessageQueueNew (2, sizeof(struct Message), &messagesQueue_attributes);

  /* creation of speedMeasQueue */
  speedMeasQueueHandle = osMessageQueueNew (1, sizeof(struct SpeedValues), &speedMeasQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of controllerTask */
  controllerTaskHandle = osThreadNew(startController, NULL, &controllerTask_attributes);

  /* creation of feedbackTask */
  feedbackTaskHandle = osThreadNew(startFeedbackTask, NULL, &feedbackTask_attributes);

  /* creation of rxTask */
  rxTaskHandle = osThreadNew(startRxTask, NULL, &rxTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* creation of messageReceived */
  messageReceivedHandle = osEventFlagsNew(&messageReceived_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_startController */
/**
  * @brief  Function implementing the controllerTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_startController */
void startController(void *argument)
{
  /* USER CODE BEGIN startController */
    configure_controller(&controllerTaskHandle, &messagesQueueHandle, &speedMeasQueueHandle);

    LOG_INFO("Start controller task\n");
    /* Infinite loop */
    for(;;)
    {
        work_controller();
    }
  /* USER CODE END startController */
}

/* USER CODE BEGIN Header_startFeedbackTask */
/**
* @brief Function implementing the feedbackTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startFeedbackTask */
void startFeedbackTask(void *argument)
{
  /* USER CODE BEGIN startFeedbackTask */
    struct FeedbackConfig feedbackConfig = {
        &speedMeasQueueHandle,
        &feedbackTaskHandle
    };
    configure_feedback(&feedbackConfig);

    LOG_INFO("Start feedback task\n");

    /* Infinite loop */
    for(;;)
    {
        work_feedback();
    }
  /* USER CODE END startFeedbackTask */
}

/* USER CODE BEGIN Header_startRxTask */
/**
* @brief Function implementing the rxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startRxTask */
void startRxTask(void *argument)
{
  /* USER CODE BEGIN startRxTask */
    configureRx(&rxTaskHandle, &messagesQueueHandle);

    LOG_INFO("Start communication task\n");
    /* Infinite loop */
    for(;;)
    {
        workRx();
    }
  /* USER CODE END startRxTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

