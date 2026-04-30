/**
 * Copyright (c) 2022 M. Kajdak. All rights reserved.
 *
 * @file           : template_tests.c
 * @brief          : Template for creating new Unity test files
 * @description    : Copy this file and modify it to create new test suites
 */

#include <tests.h>

/* Include the module being tested */
#include <your_module.h>

/* Optional: Include test utilities/mocks */
#include <stdlib.h>

/* Test fixture data (if needed) */
typedef struct {
    /* Define test context data here */
    int some_value;
} TestContext;

/* Global test context */
static TestContext ctx;

/**
 * @brief Setup function - called before each test
 *
 * Initialize test fixtures and prepare the environment for testing.
 * This is called before each individual test function.
 */
void setUp(void)
{
    /* Initialize your test context */
    ctx.some_value = 0;

    /* Set up any test fixtures */
    // my_system_init();
}

/**
 * @brief Teardown function - called after each test
 *
 * Clean up resources and restore state after testing.
 * This is called after each individual test function.
 */
void tearDown(void)
{
    /* Clean up allocated resources */
    // my_system_cleanup();

    /* Reset state */
    ctx.some_value = 0;
}

/**
 * @brief Test example with basic assertion
 *
 * Pattern: test_<function_name>_Should<ExpectedBehavior>
 * Structure: Arrange - Act - Assert
 */
void test_example_ShouldReturnCorrectValue(void)
{
    /* Arrange - Set up test data */
    int input = 42;
    int expected = 42;

    /* Act - Call the function being tested */
    int actual = my_function(input);

    /* Assert - Verify the result */
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

/**
 * @brief Test example with pointer/null checks
 */
void test_example_ShouldCreateObjectSuccessfully(void)
{
    /* Arrange */
    MyObject* obj = NULL;

    /* Act */
    obj = create_my_object();

    /* Assert - Check object was created */
    TEST_ASSERT_NOT_NULL(obj);
    TEST_ASSERT_EQUAL_INT(0, obj->initialized);

    /* Cleanup */
    destroy_my_object(obj);
}

/**
 * @brief Test example using test context
 */
void test_example_ShouldUseContextData(void)
{
    /* Arrange - Use context data from setUp() */
    ctx.some_value = 100;
    int expected = 200;

    /* Act */
    int actual = double_value(ctx.some_value);

    /* Assert */
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

/**
 * @brief Test example checking error conditions
 */
void test_example_ShouldReturnErrorForInvalidInput(void)
{
    /* Arrange */
    int invalid_input = -1;
    int expected_error = ERROR_INVALID_INPUT;

    /* Act */
    int result = my_function_with_validation(invalid_input);

    /* Assert - Verify correct error is returned */
    TEST_ASSERT_EQUAL_INT(expected_error, result);
}

/**
 * @brief Test example with double precision
 */
void test_example_ShouldCalculatePreciseValue(void)
{
    /* Arrange */
    double input = 3.14159;
    double expected = 9.8696;  /* Approximately pi squared */

    /* Act */
    double actual = calculate_value(input);

    /* Assert - Allow small floating point error */
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, expected, actual);
}

/**
 * @brief Test example with string comparison
 */
void test_example_ShouldFormatStringCorrectly(void)
{
    /* Arrange */
    char expected[] = "Hello, World!";
    char actual[50] = {0};

    /* Act */
    format_greeting(actual, sizeof(actual), "Hello", "World");

    /* Assert */
    TEST_ASSERT_EQUAL_STRING(expected, actual);
}

/* ============================================================================
 * COMMON UNITY ASSERTION MACROS
 * ============================================================================
 *
 * TEST_ASSERT_EQUAL_INT(expected, actual)
 * TEST_ASSERT_EQUAL_UINT16(expected, actual)
 * TEST_ASSERT_EQUAL_DOUBLE(expected, actual)
 * TEST_ASSERT_EQUAL_STRING(expected, actual)
 * TEST_ASSERT_TRUE(condition)
 * TEST_ASSERT_FALSE(condition)
 * TEST_ASSERT_NULL(pointer)
 * TEST_ASSERT_NOT_NULL(pointer)
 * TEST_ASSERT_EQUAL(expected, actual)
 * TEST_ASSERT_NOT_EQUAL(not_expected, actual)
 * TEST_ASSERT_LESS_THAN(threshold, actual)
 * TEST_ASSERT_GREATER_THAN(threshold, actual)
 * TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual)
 * TEST_ASSERT_HEX_EQUAL(expected, actual)
 *
 * For more macros, see: https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
 * ========================================================================== */

