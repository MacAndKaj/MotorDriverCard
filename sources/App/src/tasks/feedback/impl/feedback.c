/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motor.c
  * @brief          : Sources for motor.h file.
  ******************************************************************************
  */
#include "tasks/feedback/impl/feedback.h"

#include "log/interface.h"
#include "main/defs.h"
#include "tasks/feedback/impl/defs.h"
#include "tasks/feedback/impl/encoder.h"

static struct
{
    struct EncoderData* leftEncoder, * rightEncoder;
    osMessageQueueId_t* speedMeasQueueHandlePtr;
    osThreadId_t* feedbackThreadId;
} feedback;

void configure_feedback_impl(osMessageQueueId_t *speedMeasQueueHandle, osThreadId_t *feedbackThreadIdHandle)
{
    feedback.leftEncoder = create_encoder(LeftMotorEncoderA_GPIO_Port,
                                          LeftMotorEncoderA_Pin,
                                          LeftMotorEncoderB_GPIO_Port,
                                          LeftMotorEncoderB_Pin);
    feedback.rightEncoder = create_encoder(RightMotorEncoderA_GPIO_Port,
                                           RightMotorEncoderA_Pin,
                                           RightMotorEncoderB_GPIO_Port,
                                           RightMotorEncoderB_Pin);

    feedback.speedMeasQueueHandlePtr = speedMeasQueueHandle;
    feedback.feedbackThreadId = feedbackThreadIdHandle;
}

void work_feedback_impl()
{
    osThreadFlagsWait(PROBING_TIMEOUT_CALLBACK, osFlagsWaitAll, osWaitForever);

    static struct SpeedValues values;
    values.leftMotorSpeed = get_speed(feedback.leftEncoder);
    values.rightMotorSpeed = get_speed(feedback.rightEncoder);
    values.linearXSpeed = 0;

    osMessageQueuePut(*feedback.speedMeasQueueHandlePtr, &values, 0, 0);
}


void periodical_callback_feedback_impl()
{
    evaluate_speed(feedback.leftEncoder, SPEED_UPDATE_PERIOD);
    evaluate_speed(feedback.rightEncoder, SPEED_UPDATE_PERIOD);
    osThreadFlagsSet(*feedback.feedbackThreadId, PROBING_TIMEOUT_CALLBACK);
}

void on_ext_interrupt_feedback_impl(uint16_t GPIO_Pin)
{
    bool left = true, right = false;
    switch (GPIO_Pin)
    {
        case LeftMotorEncoderB_Pin:
            update_encoder(feedback.leftEncoder, left);
            break;
        case RightMotorEncoderB_Pin:
            update_encoder(feedback.rightEncoder, right);
            break;
        default:
            break;
    }
}
