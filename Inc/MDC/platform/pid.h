/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : pid.h
  * @brief          : Header for pid.c file.
  *                   This file contains PID structure definition and
  *                   functions declarations.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_PLATFORM_PID_H
#define MOTORDRIVER_PLATFORM_PID_H

typedef struct pid
{
    double kP;      // P factor(proportional)
    double kI;      // I factor(integral)
    double kD;      // D factor(derivative)

    double lastError;    // Last value of error used to compute new value of derivative.
    double vI;           // Variable to keep integral of error
} PID;

///Constructor of PID structures
/// \param kP: initial value of Proporiontal factor
/// \param kI: initial value of integral factor
/// \param kD: initial value of derivative factor
/// \return pointer to new PID structure
PID* createPid(double kP, double kI, double kD);

///Evaluate control value from PID handle, current error and timestamp.
/// \param pidHandle: pointer to PID structure with factors etc
/// \param error: current error = q_d - q_c
/// \return new control value
double evaluate(PID* pidHandle, double error, double dt);

///
/// \param pidHandle
void resetPid(PID* pidHandle);

#endif //MOTORDRIVER_PLATFORM_PID_H
