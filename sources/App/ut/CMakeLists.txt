set(LIBS_INSTALL_PATH ${CMAKE_BINARY_DIR}/libs)
set(LIBS_SOURCE_PATH ${CMAKE_SOURCE_DIR}/libs)
set(UNITY_PREFIX ${CMAKE_BINARY_DIR}/unity)
set(UNITY_SOURCE_DIR ${UNITY_PREFIX}/src/UnityProject)

include(ExternalProject)

# Fetch Unity framework from GitHub (just clone, no build needed)
ExternalProject_Add(UnityProject
	GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
	PREFIX ${UNITY_PREFIX}
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
)

# Unity framework paths
set(UNITY_INCLUDE_DIR ${UNITY_SOURCE_DIR}/src)
set(UNITY_SRC_DIR ${UNITY_SOURCE_DIR}/src)

include_directories(${UNITY_INCLUDE_DIR})

# Define main test runner that aggregates all tests
file(GLOB_RECURSE TEST_FILES
    platform/pid_tests.c
)

# Add Unity source file for compilation
set(UNITY_SOURCES
	${UNITY_SRC_DIR}/unity.c
)

# Add the main test executable with Unity source files
add_executable(all_tests test_runner.c ${TEST_FILES} ${UNITY_SOURCES} ${SOURCES})
add_dependencies(all_tests UnityProject)

target_include_directories(all_tests PUBLIC
	${APP_HEADERS_DIR}
	${CMAKE_SOURCE_DIR}/Core/Inc
	${CMAKE_SOURCE_DIR}/App/ut
	${UNITY_INCLUDE_DIR}
)



