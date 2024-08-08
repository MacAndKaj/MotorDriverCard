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
#include <modules/controller/interface.h>
#include <modules/feedback/interface.h>
#include <modules/syscom/interface.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
/* USER CODE BEGIN PTD */

enum event_callback_type
{
    DIRECT_CALL,
    THREAD_FLAG
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


struct event_subscription
{
    uint8_t source;
    uint8_t event_type;
    enum event_callback_type callback_type;
    union
    {
        struct direct_call_callback_info direct_call_callback_info;
        struct thread_flag_callback_info thread_flag_callback_info;
    } callback;
};

#define CALL_DIRECTLY(subscription_ptr)                                       \
    subscription_ptr->callback.direct_call_callback_info.cb(                  \
        *(subscription_ptr->callback.direct_call_callback_info.module_handle))

#define SET_FLAG(subscription_ptr)                                            \
    osThreadFlagsSet(                                                         \
        *(subscription_ptr->callback.thread_flag_callback_info.thread_id),    \
          subscription_ptr->callback.thread_flag_callback_info.thread_flag)
    

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
/* Definitions for syscomTask */
osThreadId_t syscomTaskHandle;
const osThreadAttr_t syscomTask_attributes = {
  .name = "syscomTask",
  .stack_size = 320 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for syscomMessageQueue */
osMessageQueueId_t syscomMessageQueueHandle;
uint8_t messagesQueueBuffer[ 2 * sizeof( struct Message ) ];
osStaticMessageQDef_t messagesQueueControlBlock;
const osMessageQueueAttr_t syscomMessageQueue_attributes = {
  .name = "syscomMessageQueue",
  .cb_mem = &messagesQueueControlBlock,
  .cb_size = sizeof(messagesQueueControlBlock),
  .mq_mem = &messagesQueueBuffer,
  .mq_size = sizeof(messagesQueueBuffer)
};
/* Definitions for feedbackSpeedQueue */
osMessageQueueId_t feedbackSpeedQueueHandle;
uint8_t feedbackSpeedQueueBuffer[ 2 * sizeof( struct SpeedValues ) ];
osStaticMessageQDef_t feedbackSpeedQueueControlBlock;
const osMessageQueueAttr_t feedbackSpeedQueue_attributes = {
  .name = "feedbackSpeedQueue",
  .cb_mem = &feedbackSpeedQueueControlBlock,
  .cb_size = sizeof(feedbackSpeedQueueControlBlock),
  .mq_mem = &feedbackSpeedQueueBuffer,
  .mq_size = sizeof(feedbackSpeedQueueBuffer)
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
void startSyscomTask(void *argument);

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

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of syscomMessageQueue */
  syscomMessageQueueHandle = osMessageQueueNew (2, sizeof(struct Message), &syscomMessageQueue_attributes);

  /* creation of feedbackSpeedQueue */
  feedbackSpeedQueueHandle = osMessageQueueNew (2, sizeof(struct SpeedValues), &feedbackSpeedQueue_attributes);

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
    .message_queue_handle=&messageReceivedHandle,
    .speed_values_queue_handle=&feedbackSpeedQueueHandle,
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
    
    // LOG_INFO("[controller] Start controller task\n");
    /* Infinite loop */
    for(;;)
    {
        MODULE_WORK(controller_module_handle);
    }
  /* USER CODE END startController */
}

/* USER CODE BEGIN Header_startFeedbackTask */
static struct tim_ops feedback_timers_ops[] = {
    [FEEDBACK_TIMER_INDEX] = {.start_tim=start_tim_17_it}
};

static struct encoder_data left_encoder_info = {
    .pinout = {
        .encoderAPort=LeftMotorEncoderA_GPIO_Port,
        .encoderAPin=LeftMotorEncoderA_Pin,
        .encoderBPort=LeftMotorEncoderB_GPIO_Port,
        .encoderBPin=LeftMotorEncoderB_Pin
    }
};

static struct encoder_data right_encoder_info = {
    .pinout = {
        .encoderAPort=RightMotorEncoderA_GPIO_Port,
        .encoderAPin=RightMotorEncoderA_Pin,
        .encoderBPort=RightMotorEncoderB_GPIO_Port,
        .encoderBPin=RightMotorEncoderB_Pin
    }
};

static struct feedback_data feedback_internal_data = {
    .feedback_thread_handle=&feedbackTaskHandle,
    .speed_meas_queue_handle=&feedbackSpeedQueueHandle,
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

    struct module feedback_module = {
        .ops.timers_ops=feedback_timers_ops
    };
    feedback_module_handle = &feedback_module;
    
    module_set_data(feedback_module_handle, &feedback_internal_data);
    feedback_module_init(feedback_module_handle);
    LOG_INFO("[feedback] Start task\n");

    /* Infinite loop */
    for(;;)
    {
        MODULE_WORK(feedback_module_handle);
    }
  /* USER CODE END startFeedbackTask */
}

/* USER CODE BEGIN Header_startSyscomTask */
static struct comm_ops syscom_comm_ops[] = {
    [SYSCOM_SPI_COMM_INDEX] = {.read_non_blocking=start_spi_2_dma_reception}
};

static struct syscom_data syscom_task_data = {
    .syscom_thread_handle=&syscomTaskHandle,
    .received_messages_queue_handle=&syscomMessageQueueHandle,
};

static struct module *syscom_module_handle;

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
    
    struct module syscom_module = {
        .ops.communication_ops = syscom_comm_ops
    };
    syscom_module_handle = &syscom_module;
    
    module_set_data(syscom_module_handle, &syscom_task_data);
    syscom_module_init(syscom_module_handle);

    LOG_INFO("[syscom] Start task\n");
    /* Infinite loop */
    for(;;)
    {
        MODULE_WORK(syscom_module_handle);
    }
  /* USER CODE END startSyscomTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

static struct event_subscription spi_subscriptions[] = {
    {
        .event_type=SPI_EVENT_RX_CPLT,
        .source=SPI_INSTANCE_2,
        .callback_type=THREAD_FLAG,
        .callback.thread_flag_callback_info={
            .thread_id=&syscomTaskHandle,
            .thread_flag=DATA_RECEIVED_THREAD_FLAG,
        }
    },
};

void spi_event(uint8_t instance, uint8_t event)
{
    static int length = sizeof(spi_subscriptions) / sizeof(struct event_subscription);
    struct event_subscription *ptr;
    for (int i = 0; i < length; ++i)
    {
        ptr = spi_subscriptions + i;
        if ((ptr->source == instance) && (ptr->event_type == event))
        {
            if (ptr->callback_type == DIRECT_CALL) CALL_DIRECTLY(ptr);
            else if (ptr->callback_type == THREAD_FLAG) SET_FLAG(ptr);
        }
    }

}

static struct event_subscription tim_subscriptions[] = {
    {
        .event_type=TIM_EVENT_IT,
        .source=TIM_INSTANCE_17,
        .callback_type=DIRECT_CALL,
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
            if (ptr->callback_type == DIRECT_CALL) CALL_DIRECTLY(ptr);
            else if (ptr->callback_type == THREAD_FLAG) SET_FLAG(ptr);
        }
    }
}

static struct event_subscription exti_subscriptions[] = {
    {
        .event_type=EXTI_EVENT_IT,
        .source=LEFT_MOTOR_ENCODER_PIN_B,
        .callback_type=DIRECT_CALL,
        .callback.direct_call_callback_info={
            .cb=feedback_exti_left_callback,
            .module_handle=&feedback_module_handle
        }
    },
    {
        .event_type=EXTI_EVENT_IT,
        .source=RIGHT_MOTOR_ENODER_PIN_B,
        .callback_type=DIRECT_CALL,
        .callback.direct_call_callback_info={
            .cb=feedback_exti_right_callback,
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
            if (ptr->callback_type == DIRECT_CALL) CALL_DIRECTLY(ptr);
            else if (ptr->callback_type == THREAD_FLAG) SET_FLAG(ptr);
        }
    }
}

/* USER CODE END Application */

