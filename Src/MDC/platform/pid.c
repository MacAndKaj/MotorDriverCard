/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : pid.c
  * @brief          : Sources for pid.h file.
  *                   This file contains definitions of functions for PID control.
  *                   TODO: usage of numerical integrating library
  ******************************************************************************
  */

#include <MDC/platform/pid.h>

#include <assert.h>

double getKP(const PID* pidHandle);
double getKI(const PID* pidHandle);
double getKD(const PID* pidHandle);
double getLastError(const PID* pidHandle);
void setLastError(PID* pidHandle, double val);
double getIntegral(const PID* pidHandle);
void setIntegral(PID* pidHandle, double val);

double evaluate(PID* pid, double error, double dt)
{
    assert(dt != 0.);

    double derivative = (error - getLastError(pid))/dt;
    double integral =  getIntegral(pid) + error*dt;

    double output = (getKP(pid) * error) + (getKI(pid) * integral) + (getKD(pid) * derivative);

    setIntegral(pid, integral);
    setLastError(pid, error);

    return output;
}

double getKP(const PID* pidHandle)
{
    return pidHandle->kP;
}

double getKI(const PID* pidHandle)
{
    return pidHandle->kI;
}

double getKD(const PID* pidHandle)
{
    return pidHandle->kD;
}

double getLastError(const PID* pidHandle)
{
    return pidHandle->lastError;
}

void setLastError(PID* pidHandle, double val)
{
    pidHandle->lastError = val;
}

double getIntegral(const PID* pidHandle)
{
    return pidHandle->vI;
}

void setIntegral(PID* pidHandle, double val)
{
    pidHandle->vI = val;
}

void resetPid(PID* pidHandle)
{
    pidHandle->vI = 0;
    pidHandle->lastError = 0;
}