/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : pid_tests.c
  * @brief          : Tests for pid.h/c
  ******************************************************************************
  */

#include <tests.h>

#include <modules/controller/impl/pid.h>

void setUp(void)
{
	/* Initialize before each test */
}

void tearDown(void)
{
	/* Cleanup after each test */
}

void test_evaluate_ShouldReturnOutputEqualToErrorIfDtIsZero(void)
{
	static const double sampleError = 10.;
	struct pid sut = create_pid(1.0, 1.0, 1.0);
	TEST_ASSERT_EQUAL_DOUBLE(sampleError, pid_evaluate(&sut, sampleError, 0.));
}