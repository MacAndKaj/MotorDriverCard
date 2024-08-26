####################################################
# Copyright (c) 2024 M. Kajdak. All rights reserved.
####################################################
set(LIBRARY_NAME library_mdc_app_main)

set(APP_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(GLOB MAIN_SOURCES
    # HEADERS
    ${APP_HEADERS_DIR}/main/boolean.h
    ${APP_HEADERS_DIR}/main/defs.h
    ${APP_HEADERS_DIR}/main/module.h
)

add_subdirectory(msg)
add_subdirectory(modules)

add_library(${LIBRARY_NAME} INTERFACE)

target_include_directories(${LIBRARY_NAME}
    INTERFACE ${APP_HEADERS_DIR}
)

