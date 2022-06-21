set(TEST_SUITE PLATFORM_TESTS_RUN)

file(GLOB TESTS_FILES
  pid_tests.c
  )

add_executable(${TEST_SUITE} ${TESTS_FILES} ${SOURCES})

target_link_libraries(${TEST_SUITE} unity)