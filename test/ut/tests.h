/**
  * Copyright (c) 2022 M. Kajdak. All rights reserved.
  */

#define UNITY_INT_WIDTH (16)
#include <unity.h>

#define TEST_FIXTURE(name) \
    static void test_##name(void)

#define ADD_TEST(name) \
    RUN_TEST(test_##name(void))
