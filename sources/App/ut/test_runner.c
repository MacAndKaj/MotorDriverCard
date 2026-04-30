/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : test_runner.c
  * @brief          : Unified test runner aggregating all test suites
  ******************************************************************************
  */

#include <tests.h>


/* Platform tests declarations */
void test_evaluate_ShouldReturnOutputEqualToErrorIfDtIsZero(void);

int main(void)
{
    UNITY_BEGIN();

    /* Run platform tests */
    RUN_TEST(test_evaluate_ShouldReturnOutputEqualToErrorIfDtIsZero);

    return UNITY_END();
}

