/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : encoder.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef INC_MDC_FEEDBACK_IMPL_ENCODER_H
#define INC_MDC_FEEDBACK_IMPL_ENCODER_H

#include <main.h>

#include <stdbool.h>

struct EncoderData;

struct EncoderData* create_encoder(GPIO_TypeDef* encoderAPort, uint16_t encoderAPin,
                                   GPIO_TypeDef* encoderBPort, uint16_t encoderBPin);

void update_encoder(struct EncoderData* handle, bool leftSide);

void evaluate_speed(struct EncoderData *handle, double t);

double get_speed(const struct EncoderData *handle);

#endif //INC_MDC_FEEDBACK_IMPL_ENCODER_H
