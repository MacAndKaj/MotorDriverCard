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
#include <modules/log/interface.h>
#include <main/defs.h>
#include <main/module.h>
#include <msg/defs/Message.h> // Change to lowercase
#include <msg/message_ids.h> // Change to lowercase
#include <modules/controller/interface.h>
#include <modules/feedback/interface.h>
#include <modules/monitoring/interface.h>
#include <modules/syscom/interface.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
/* USER CODE BEGIN PTD */

enum event_callback_type
{
    MODULE_CALL,
    THREAD_FLAG,
    RAW_CALLBACK
};

typedef void (*direct_call_callback_t)(struct module *);

struct direct_call_callback_info
{
    struct module **module_handle;
    direct_call_callback_t cb;
};

struct thread_flag_callback_info
{
    osThreadId_t *thread_id;
    uint32_t thread_flag;
};

typedef void (*raw_callback_t)();

struct event_subscription
{
    uint8_t source;
    uint8_t event_type;
    enum event_callback_type callback_type;
    union
    {
        struct direct_call_callback_info direct_call_callback_info;
        struct thread_flag_callback_info thread_flag_callback_info;
        raw_callback_t raw_callback;
    } callback;
};

#define CALL_DIRECTLY(subscription_ptr)                                                 \
    if (*(subscription_ptr->callback.direct_call_callback_info.module_handle) != NULL)  \
    {                                                                                   \
        subscription_ptr->callback.direct_call_callback_info.cb(                        \
            *(subscription_ptr->callback.direct_call_callback_info.module_handle));     \
    }

#define SET_FLAG(subscription_ptr)                                            \
    osThreadFlagsSet(                                                         \
        *(subscription_ptr->callback.thread_flag_callback_info.thread_id),    \
          subscription_ptr->callback.thread_flag_callback_info.thread_flag);
    

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TICKS_PER_HZ 1000U
#define ONE_TICK 1U
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */


/* USER CODE END Variables */
/* Definitions for controllerTask */
osThreadId_t controllerTaskHandle;
uint32_t controllerTaskBuffer[ 320 ];
osStaticThreadDef_t controllerTaskControlBlock;
const osThreadAttr_t controllerTask_attributes = {
  .name = "controllerTask",
  .cb_mem = &controllerTaskControlBlock,
  .cb_size = sizeof(controllerTaskControlBlock),
  .stack_mem = &controllerTaskBuffer[0],
  .stack_size = sizeof(controllerTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for feedbackTask */
osThreadId_t feedbackTaskHandle;
uint32_t feedbackTaskBuffer[ 320 ];
osStaticThreadDef_t feedbackTaskControlBlock;
const osThreadAttr_t feedbackTask_attributes = {
  .name = "feedbackTask",
  .cb_mem = &feedbackTaskControlBlock,
  .cb_size = sizeof(feedbackTaskControlBlock),
  .stack_mem = &feedbackTaskBuffer[0],
  .stack_size = sizeof(feedbackTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for syscomTask */
osThreadId_t syscomTaskHandle;
uint32_t syscomTaskBuffer[ 320 ];
osStaticThreadDef_t syscomTaskControlBlock;
const osThreadAttr_t syscomTask_attributes = {
  .name = "syscomTask",
  .cb_mem = &syscomTaskControlBlock,
  .cb_size = sizeof(syscomTaskControlBlock),
  .stack_mem = &syscomTaskBuffer[0],
  .stack_size = sizeof(syscomTaskBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for monitoringTask */
osThreadId_t monitoringTaskHandle;
uint32_t monitoringTaskBuffer[ 320 ];
osStaticThreadDef_t monitoringTaskControlBlock;
const osThreadAttr_t monitoringTask_attributes = {
  .name = "monitoringTask",
  .cb_mem = &monitoringTaskControlBlock,
  .cb_size = sizeof(monitoringTaskControlBlock),
  .stack_mem = &monitoringTaskBuffer[0],
  .stack_size = sizeof(monitoringTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for controllerMessageQueue */
osMessageQueueId_t controllerMessageQueueHandle;
uint8_t controllerMessageQueueBuffer[ 1 * sizeof( struct Message ) ];
osStaticMessageQDef_t controllerMessageQueueControlBlock;
const osMessageQueueAttr_t controllerMessageQueue_attributes = {
  .name = "controllerMessageQueue",
  .cb_mem = &controllerMessageQueueControlBlock,
  .cb_size = sizeof(controllerMessageQueueControlBlock),
  .mq_mem = &controllerMessageQueueBuffer,
  .mq_size = sizeof(controllerMessageQueueBuffer)
};
/* Definitions for controllerInternalMessageQueue */
osMessageQueueId_t controllerInternalMessageQueueHandle;
uint8_t controllerInternalMessageQueueBuffer[ 2 * sizeof( struct InternalMessage ) ];
osStaticMessageQDef_t controllerInternalMessageQueueControlBlock;
const osMessageQueueAttr_t controllerInternalMessageQueue_attributes = {
  .name = "controllerInternalMessageQueue",
  .cb_mem = &controllerInternalMessageQueueControlBlock,
  .cb_size = sizeof(controllerInternalMessageQueueControlBlock),
  .mq_mem = &controllerInternalMessageQueueBuffer,
  .mq_size = sizeof(controllerInternalMessageQueueBuffer)
};
/* Definitions for syscomTxMessageQueue */
osMessageQueueId_t syscomTxMessageQueueHandle;
uint8_t syscomTxMessageQueueBuffer[ 3 * sizeof( struct Message ) ];
osStaticMessageQDef_t syscomTxMessageQueueControlBlock;
const osMessageQueueAttr_t syscomTxMessageQueue_attributes = {
  .name = "syscomTxMessageQueue",
  .cb_mem = &syscomTxMessageQueueControlBlock,
  .cb_size = sizeof(syscomTxMessageQueueControlBlock),
  .mq_mem = &syscomTxMessageQueueBuffer,
  .mq_size = sizeof(syscomTxMessageQueueBuffer)
};
/* Definitions for monitoringMessageQueue */
osMessageQueueId_t monitoringMessageQueueHandle;
uint8_t monitoringMessageQueueBuffer[ 1 * sizeof( struct Message ) ];
osStaticMessageQDef_t monitoringMessageQueueControlBlock;
const osMessageQueueAttr_t monitoringMessageQueue_attributes = {
  .name = "monitoringMessageQueue",
  .cb_mem = &monitoringMessageQueueControlBlock,
  .cb_size = sizeof(monitoringMessageQueueControlBlock),
  .mq_mem = &monitoringMessageQueueBuffer,
  .mq_size = sizeof(monitoringMessageQueueBuffer)
};
/* Definitions for monitoringInternalMessageQueue */
osMessageQueueId_t monitoringInternalMessageQueueHandle;
uint8_t monitoringInternalMessageQueueBuffer[ 2 * sizeof( struct InternalMessage ) ];
osStaticMessageQDef_t monitoringInternalMessageQueueControlBlock;
const osMessageQueueAttr_t monitoringInternalMessageQueue_attributes = {
  .name = "monitoringInternalMessageQueue",
  .cb_mem = &monitoringInternalMessageQueueControlBlock,
  .cb_size = sizeof(monitoringInternalMessageQueueControlBlock),
  .mq_mem = &monitoringInternalMessageQueueBuffer,
  .mq_size = sizeof(monitoringInternalMessageQueueBuffer)
};
/* Definitions for syscomMasterTriggerTimer */
osTimerId_t syscomMasterTriggerTimerHandle;
osStaticTimerDef_t syscomMasterTriggerTimerControlBlock;
const osTimerAttr_t syscomMasterTriggerTimer_attributes = {
  .name = "syscomMasterTriggerTimer",
  .cb_mem = &syscomMasterTriggerTimerControlBlock,
  .cb_size = sizeof(syscomMasterTriggerTimerControlBlock),
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
void log_uart_handler(UART_HandleTypeDef *huart);
void send_syscom_message_handler(const struct Message *msg);
/* USER CODE END FunctionPrototypes */

void startController(void *argument);
void startFeedbackTask(void *argument);
void startSyscomTask(void *argument);
void startMonitoringTask(void *argument);
void syscomMasterTriggerTimerCallback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of logMutex */
  logMutexHandle = osMutexNew(&logMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
    configure_log(&logMutexHandle, transmit_uart2);
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of syscomMasterTriggerTimer */
  syscomMasterTriggerTimerHandle = osTimerNew(syscomMasterTriggerTimerCallback, osTimerOnce, NULL, &syscomMasterTriggerTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of controllerMessageQueue */
  controllerMessageQueueHandle = osMessageQueueNew (1, sizeof(struct Message), &controllerMessageQueue_attributes);

  /* creation of controllerInternalMessageQueue */
  controllerInternalMessageQueueHandle = osMessageQueueNew (2, sizeof(struct InternalMessage), &controllerInternalMessageQueue_attributes);

  /* creation of syscomTxMessageQueue */
  syscomTxMessageQueueHandle = osMessageQueueNew (3, sizeof(struct Message), &syscomTxMessageQueue_attributes);

  /* creation of monitoringMessageQueue */
  monitoringMessageQueueHandle = osMessageQueueNew (1, sizeof(struct Message), &monitoringMessageQueue_attributes);

  /* creation of monitoringInternalMessageQueue */
  monitoringInternalMessageQueueHandle = osMessageQueueNew (2, sizeof(struct InternalMessage), &monitoringInternalMessageQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of controllerTask */
  controllerTaskHandle = osThreadNew(startController, NULL, &controllerTask_attributes);

  /* creation of feedbackTask */
  feedbackTaskHandle = osThreadNew(startFeedbackTask, NULL, &feedbackTask_attributes);

  /* creation of syscomTask */
  syscomTaskHandle = osThreadNew(startSyscomTask, NULL, &syscomTask_attributes);

  /* creation of monitoringTask */
  monitoringTaskHandle = osThreadNew(startMonitoringTask, NULL, &monitoringTask_attributes);

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

static struct motor_info left_motor_info = {
    .pinout={
        .motorControl1Port=LeftMotorIn1_GPIO_Port,
        .motorControl1Pin=LeftMotorIn1_Pin,
        .motorControl2Port=LeftMotorIn2_GPIO_Port,
        .motorControl2Pin=LeftMotorIn2_Pin,
    },
    .start_pwm=start_tim_2_pwm_dma,
};

static struct motor_info right_motor_info = {
    .pinout={
        .motorControl1Port=RightMotorIn1_GPIO_Port,
        .motorControl1Pin=RightMotorIn1_Pin,
        .motorControl2Port=RightMotorIn2_GPIO_Port,
        .motorControl2Pin=RightMotorIn2_Pin,
    },
    .start_pwm=start_tim_3_pwm_dma,
};

static struct controller_data controller_module_data = {
    .controller_thread_handle=&controllerTaskHandle,
    .message_queue_handle=&controllerMessageQueueHandle,
    .internal_message_queue_handle=&controllerInternalMessageQueueHandle,
    .left_motor_info=&left_motor_info,
    .right_motor_info=&right_motor_info,
};

static struct module *controller_module_handle;

/**
  * @brief  Function implementing the controllerTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_startController */
void startController(void *argument)
{
  /* USER CODE BEGIN startController */
    (void)argument;
    
    struct module controller_module;

    controller_module_handle = &controller_module;
    
    module_set_data(controller_module_handle, &controller_module_data);
    controller_module_init(controller_module_handle);
    
     LOG_INFO("[controller] Start\n");
    /* Infinite loop */
    for(;;)
    {
        MODULE_WORK(controller_module_handle);
    }
  /* USER CODE END startController */
}

/* USER CODE BEGIN Header_startFeedbackTask */
static struct message_subscription feedback_subscribers[] = {
    {.msg_id=SPEED_VALUES_MSG_ID, .subscription_queue=&controllerInternalMessageQueueHandle},
    {.msg_id=SPEED_VALUES_MSG_ID, .subscription_queue=&monitoringInternalMessageQueueHandle}
};

static struct tim_ops feedback_timers_ops[] = {
    [FEEDBACK_TIMER_INDEX] = {.start_tim=start_tim_17_it}
};

static struct encoder_data left_encoder_info = {
    .start_encoder=start_tim_8_encoder,
    .get_encoder_pulses=get_tim_8_encoder_count
};

static struct encoder_data right_encoder_info = {
    .start_encoder=start_tim_4_encoder,
    .get_encoder_pulses=get_tim_4_encoder_count
};

static struct feedback_data feedback_internal_data = {
    .feedback_thread_handle=&feedbackTaskHandle,
    .left_encoder_data=&left_encoder_info,
    .right_encoder_data=&right_encoder_info,
};

static struct module *feedback_module_handle;

/**
* @brief Function implementing the feedbackTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startFeedbackTask */
void startFeedbackTask(void *argument)
{
  /* USER CODE BEGIN startFeedbackTask */
    (void)argument;

    feedback_internal_data.subs = feedback_subscribers;
    feedback_internal_data.subs_len = ARRAY_LEN(feedback_subscribers);

    struct module feedback_module = {
        .ops.timers_ops=feedback_timers_ops
    };
    feedback_module_handle = &feedback_module;

    module_set_data(feedback_module_handle, &feedback_internal_data);
    feedback_module_init(feedback_module_handle);
    LOG_INFO("[feedback] Start\n");

    /* Infinite loop */
    for(;;)
    {
        MODULE_WORK(feedback_module_handle);
    }
  /* USER CODE END startFeedbackTask */
}

/* USER CODE BEGIN Header_startSyscomTask */
static struct message_subscription syscom_subscriptions[] = {
    {.msg_id=CMD_SET_MOTOR_SPEED_ID, .subscription_queue=&controllerMessageQueueHandle},
    {.msg_id=PLATFORM_POLL_STATUS_REQ_ID, .subscription_queue=&monitoringMessageQueueHandle}
};

static struct comm_ops syscom_comm_ops[] = {
    [SYSCOM_SPI_COMM_INDEX] = {
        .read_non_blocking=start_spi_2_dma_reception,
        .write_non_blocking=start_spi_2_dma_transfer,
        .write_and_read_non_blocking=start_spi2_dma_transfer_and_reception
    }
};

static struct syscom_data syscom_task_data = {
    .syscom_thread_handle=&syscomTaskHandle,
    .transferred_messages_queue_handle=&syscomTxMessageQueueHandle,
};

static struct module *syscom_module_handle;
typedef void (*module_os_timer_callback)(struct module*);
static module_os_timer_callback syscom_os_timer_callback = NULL;

// TODO: move it somewhere else - it's not a part of global setup
void send_syscom_message_handler(const struct Message *msg)
{
    if (osMessageQueuePut(syscomTxMessageQueueHandle, msg, 0, 0) != osOK)
    {
        LOG_INFO("[syscom] Fail sending message\n");
    }
    osThreadFlagsSet(syscomTaskHandle, DATA_TX_BUFFERED_THREAD_FLAG);
}

/**
* @brief Function implementing the syscomTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startSyscomTask */
void startSyscomTask(void *argument)
{
  /* USER CODE BEGIN startSyscomTask */
    (void)argument;

    syscom_task_data.subs = syscom_subscriptions;
    syscom_task_data.subs_len = ARRAY_LEN(syscom_subscriptions);
    
    struct module syscom_module = {
        .ops.communication_ops = syscom_comm_ops
    };
    syscom_module_handle = &syscom_module;
    
    module_set_data(syscom_module_handle, &syscom_task_data);
    syscom_module_init(syscom_module_handle);
    syscom_os_timer_callback = syscom_module_timer_callback;

    LOG_INFO("[syscom] Start\n");
    /* Infinite loop */
    for(;;)
    {
        MODULE_WORK(syscom_module_handle);
    }
  /* USER CODE END startSyscomTask */
}

/* USER CODE BEGIN Header_startMonitoringTask */


static struct module *monitoring_module_handle;

/**
* @brief Function implementing the monitorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startMonitoringTask */
void startMonitoringTask(void *argument)
{
  /* USER CODE BEGIN startMonitoringTask */
  (void)argument;

  struct monitoring_data monitoring_task_data = {
    .syscom_message_queue_handle=&monitoringMessageQueueHandle,
    .internal_message_queue_handle=&monitoringInternalMessageQueueHandle,
    .send_syscom_message=send_syscom_message_handler
  };
  struct module monitoring_module;

  monitoring_module_handle = &monitoring_module;
  module_set_data(monitoring_module_handle, &monitoring_task_data);
  monitoring_module_init(monitoring_module_handle);
  LOG_INFO("[monitoring] Start\n");

  /* Infinite loop */
  for(;;)
  {
      MODULE_WORK(monitoring_module_handle);
  }
  /* USER CODE END startMonitoringTask */
}

/* syscomMasterTriggerTimerCallback function */
__weak void syscomMasterTriggerTimerCallback(void *argument)
{
  /* USER CODE BEGIN syscomMasterTriggerTimerCallback */
  (void)argument;
  (*syscom_os_timer_callback)(syscom_module_handle);
  /* USER CODE END syscomMasterTriggerTimerCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

#define SUBSCRIPTIONS_LEN 3
static struct event_subscription spi_subscriptions[SUBSCRIPTIONS_LEN] = {
    {
        .event_type=SPI_EVENT_TX_RX_CPLT,
        .source=SPI_INSTANCE_2,
        .callback_type=THREAD_FLAG,
        .callback.thread_flag_callback_info={
            .thread_id=&syscomTaskHandle,
            .thread_flag=DATA_RECEIVED_THREAD_FLAG,
        }
    }
};

void spi_event(uint8_t instance, uint8_t event)
{
    struct event_subscription *ptr = spi_subscriptions;
    for (int i = 0; i < SUBSCRIPTIONS_LEN; ++i)
    {
        if ((ptr->source == instance) && (ptr->event_type == event))
        {
            if (ptr->callback_type == RAW_CALLBACK)
            {
                ptr->callback.raw_callback();
            }
            else if (ptr->callback_type == MODULE_CALL)
            {
                CALL_DIRECTLY(ptr);
            }
            else if (ptr->callback_type == THREAD_FLAG)
            {
                SET_FLAG(ptr)
            }
        }
        ++ptr;
    }
}

static struct event_subscription tim_subscriptions[] = {
    {
        .event_type=TIM_EVENT_IT,
        .source=TIM_INSTANCE_17,
        .callback_type=MODULE_CALL,
        .callback.direct_call_callback_info={
            .cb=feedback_timer_callback,
            .module_handle=&feedback_module_handle
        }
    }
};

void tim_event(uint8_t instance, uint8_t event_type)
{
    static int length = sizeof(tim_subscriptions) / sizeof(struct event_subscription);
    struct event_subscription *ptr;
    for (int i = 0; i < length; ++i)
    {
        ptr = tim_subscriptions + i;
        if ((ptr->source == instance) && (ptr->event_type == event_type))
        {
            if (ptr->callback_type == MODULE_CALL)
            {
                CALL_DIRECTLY(ptr)
            }
            else if (ptr->callback_type == THREAD_FLAG)
            {
                SET_FLAG(ptr)
            }
        }
    }
}

static struct event_subscription exti_subscriptions[] = {
    {
        .event_type=EXTI_EVENT_IT,
        .source=0,
        .callback_type=MODULE_CALL,
        .callback.direct_call_callback_info={
            .cb=NULL,
            .module_handle=&feedback_module_handle
        }
    },
};

void exti_event(uint8_t instance, uint8_t event_type)
{
    static int length = sizeof(exti_subscriptions) / sizeof(struct event_subscription);
    struct event_subscription *ptr;
    for (int i = 0; i < length; ++i)
    {
        ptr = exti_subscriptions + i;
        if ((ptr->source == instance) && (ptr->event_type == event_type))
        {
            if (ptr->callback_type == MODULE_CALL)
            {
                CALL_DIRECTLY(ptr)
            }
            else if (ptr->callback_type == THREAD_FLAG)
            {
                SET_FLAG(ptr)
            }
        }
    }
}

/* USER CODE END Application */

