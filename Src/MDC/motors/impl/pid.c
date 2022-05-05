/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : pid.c
  * @brief          : Sources for pid.h file.
  *                   This file contains definitions of functions for struct PIDParameters control.
  *                   TODO: usage of numerical integrating library
  ******************************************************************************
  */

#include <MDC/motors/impl/pid.h>

#include <assert.h>

double getKP(const struct PIDParameters* pidHandle);
double getKI(const struct PIDParameters* pidHandle);
double getKD(const struct PIDParameters* pidHandle);
double getLastError(const struct PIDParameters* pidHandle);
void setLastError(struct PIDParameters* pidHandle, double val);
double getIntegral(const struct PIDParameters* pidHandle);
void setIntegral(struct PIDParameters* pidHandle, double val);

double pid_evaluate(struct PIDParameters* pidHandle, double error, double dt)
{
    assert(dt != 0.);

    double derivative = (error - getLastError(pidHandle)) / dt;
    double integral = getIntegral(pidHandle) + error * dt;

    double output = (getKP(pidHandle) * error) + (getKI(pidHandle) * integral) + (getKD(pidHandle) * derivative);

    setIntegral(pidHandle, integral);
    setLastError(pidHandle, error);

    return output;
}

double getKP(const struct PIDParameters* pidHandle)
{
    return pidHandle->kP;
}

double getKI(const struct PIDParameters* pidHandle)
{
    return pidHandle->kI;
}

double getKD(const struct PIDParameters* pidHandle)
{
    return pidHandle->kD;
}

double getLastError(const struct PIDParameters* pidHandle)
{
    return pidHandle->lastError;
}

void setLastError(struct PIDParameters* pidHandle, double val)
{
    pidHandle->lastError = val;
}

double getIntegral(const struct PIDParameters* pidHandle)
{
    return pidHandle->vI;
}

void setIntegral(struct PIDParameters* pidHandle, double val)
{
    pidHandle->vI = val;
}

void resetPid(struct PIDParameters* pidHandle)
{
    pidHandle->vI = 0;
    pidHandle->lastError = 0;
}