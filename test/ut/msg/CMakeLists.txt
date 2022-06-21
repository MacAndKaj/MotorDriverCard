set(TEST_SUITE MSG_TESTS_RUN)

file(GLOB TESTS_FILES
  messages_size_map_tests.c
  )

add_executable(${TEST_SUITE} ${TESTS_FILES} ${SOURCES})
add_dependencies(${TEST_SUITE} Unity)

target_link_libraries(${TEST_SUITE} unity)