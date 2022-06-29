/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : motor.c
  * @brief          : Sources for motor.h file.
  ******************************************************************************
  */
#include <MDC/feedback//impl/feedback.h>

#include <MDC/main/defs.h>
#include <MDC/feedback/impl/defs.h>
#include <MDC/feedback/impl/encoder.h>

struct
{
    struct EncoderData* leftEncoder, * rightEncoder;
} feedback;

osMessageQueueId_t* speedMeasQueueHandlePtr;

void configure_feedback_impl()
{
    feedback.leftEncoder = create_encoder(LeftMotorEncoderA_GPIO_Port,
                                          LeftMotorEncoderA_Pin,
                                          LeftMotorEncoderB_GPIO_Port,
                                          LeftMotorEncoderB_Pin);
    feedback.rightEncoder = create_encoder(RightMotorEncoderA_GPIO_Port,
                                           RightMotorEncoderA_Pin,
                                           RightMotorEncoderB_GPIO_Port,
                                           RightMotorEncoderB_Pin);
}

void work_feedback_impl()
{
    struct SpeedValues values = {
        .leftMotorSpeed=get_speed(feedback.leftEncoder),
        .rightMotorSpeed=get_speed(feedback.rightEncoder),
        .linearXSpeed=0
    };

    osMessageQueuePut(*speedMeasQueueHandlePtr, &values, 0, 0);
}

void periodical_callback_controller_impl()
{
    evaluate_speed(feedback.leftEncoder, SPEED_UPDATE_PERIOD);
    evaluate_speed(feedback.rightEncoder, SPEED_UPDATE_PERIOD);
//    osThreadFlagsSet(*motorsContext.threadIdHandle, PROBING_TIMEOUT_CALLBACK);
}

void on_ext_interrupt_controller_impl(uint16_t GPIO_Pin)
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
