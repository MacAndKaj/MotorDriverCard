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

struct pid
{
    double k_p;           // P factor(proportional)
    double k_i;           // I factor(integral)
    double k_d;           // D factor(derivative)

    double last_error;    // Last value of error used to compute new value of derivative.
    double v_i;           // Variable to keep integral of error
};

///Constructor of PID structures
/// \param kP: initial value of Proporiontal factor
/// \param kI: initial value of integral factor
/// \param kD: initial value of derivative factor
/// \return pointer to new PID structure
struct pid create_pid(double p, double i, double d);

///Evaluate control value from PID handle, current error and timestamp.
/// \param pidHandle: pointer to PID structure with factors etc
/// \param error: current error = q_d - q_c
/// \return new control value
double pid_evaluate(struct pid* handle, double error, double dt);

///
/// \param pidHandle
void reset_pid(struct pid* handle);

#endif //MDC_CONTROLLER_IMPL_PID_H
