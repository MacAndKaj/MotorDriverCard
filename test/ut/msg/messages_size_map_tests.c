/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : messages_size_map_tests.c
  * @brief          : Tests for messages_size_map.h/c
  ******************************************************************************
  */

#include <tests.h>

#include <msg/messages_size_map.h>

#include <msg/defs/PlatformSetMotorSpeed.h>

#define UNKNOWN_VALUE 0

void setUp(void)
{
    // dummy
}

void tearDown(void)
{
    // dummy
}

void test_messages_size_map_findSizeForMessageId_ShouldReturnCorrectValue(void)
{
  uint16_t msgSize = findSizeForMessageId(PLATFORM_SET_MOTOR_SPEED_REQ_ID);
	TEST_ASSERT_EQUAL_UINT16(msgSize, sizeof(PlatformSetMotorSpeedReq));
}

void test_messages_size_map_findSizeForMessageId_ShouldReturnZeroIfNotFound(void)
{
  uint16_t msgSize = findSizeForMessageId(UNKNOWN_VALUE);
  TEST_ASSERT_EQUAL_UINT16(msgSize, 0);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_messages_size_map_findSizeForMessageId_ShouldReturnCorrectValue);
    RUN_TEST(test_messages_size_map_findSizeForMessageId_ShouldReturnZeroIfNotFound);
    return UNITY_END();
}