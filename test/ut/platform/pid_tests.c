/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : pid_tests.c
  * @brief          : Tests for pid.h/c
  ******************************************************************************
  */

#include <unity.h>

#include <MDC/platform/pid.h>

#include <stdlib.h>

PID* sut;

void setUp(void)
{
	sut = createPid(1.0, 1.0, 1.0);
}

void tearDown(void)
{
	free(sut);
}


void test_evaluate_ShouldReturnOutputEqualToErrorIfDtIsZero(void)
{
	static const double sampleError = 10.;
	TEST_ASSERT_EQUAL_DOUBLE(evaluate(sut, sampleError, 0.), sampleError);
}