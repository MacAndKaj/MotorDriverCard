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
#ifndef MDC_CONTROLLER_IMPL_PID_H
#define MDC_CONTROLLER_IMPL_PID_H

struct PIDParameters
{
    double kP;      // P factor(proportional)
    double kI;      // I factor(integral)
    double kD;      // D factor(derivative)

    double lastError;    // Last value of error used to compute new value of derivative.
    double vI;           // Variable to keep integral of error
};

///Constructor of PID structures
/// \param kP: initial value of Proporiontal factor
/// \param kI: initial value of integral factor
/// \param kD: initial value of derivative factor
/// \return pointer to new PID structure
struct PIDParameters create_pid(double kP, double kI, double kD);

///Evaluate control value from PID handle, current error and timestamp.
/// \param pidHandle: pointer to PID structure with factors etc
/// \param error: current error = q_d - q_c
/// \return new control value
double pid_evaluate(struct PIDParameters* pidHandle, double error, double dt);

///
/// \param pidHandle
void reset_pid(struct PIDParameters* pidHandle);

#endif //MDC_CONTROLLER_IMPL_PID_H
