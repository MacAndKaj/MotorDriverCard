/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : pid.c
  * @brief          : Sources for pid.h file.
  *                   This file contains definitions of functions for struct pid control.
  *                   TODO: usage of numerical integrating library
  ******************************************************************************
  */

#include <modules/controller/impl/pid.h>

#include <assert.h>

double get_k_p(const struct pid* handle);
double get_k_i(const struct pid* handle);
double get_k_d(const struct pid* handle);
double get_last_error(const struct pid* handle);
void set_last_error(struct pid* handle, double val);
double get_integral(const struct pid* handle);
void set_integral(struct pid* handle, double val);

struct pid create_pid(double p, double i, double d)
{
    struct pid tmp = {.k_p=p, .k_i=i, .k_d=d, .v_i=0, .last_error=0};
    return tmp;
}

double pid_evaluate(struct pid* handle, double error, double dt)
{
    assert(dt != 0.);

    double derivative = (error - get_last_error(handle)) / dt;
    double integral = get_integral(handle) + ((get_last_error(handle) + error)*dt)/2;

    double output = (get_k_p(handle) * error) + (get_k_i(handle) * integral) + (get_k_d(handle) * derivative);

    set_integral(handle, integral);
    set_last_error(handle, error);

    return output;
}

double get_k_p(const struct pid* handle)
{
    return handle->k_p;
}

double get_k_i(const struct pid* handle)
{
    return handle->k_i;
}

double get_k_d(const struct pid* handle)
{
    return handle->k_d;
}

double get_last_error(const struct pid* handle)
{
    return handle->last_error;
}

void set_last_error(struct pid* handle, double val)
{
    handle->last_error = val;
}

double get_integral(const struct pid* handle)
{
    return handle->v_i;
}

void set_integral(struct pid* handle, double val)
{
    handle->v_i = val;
}

void reset_pid(struct pid* handle)
{
    handle->v_i = 0;
    handle->last_error = 0;
}