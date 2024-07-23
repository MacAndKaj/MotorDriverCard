####################################################
# Copyright (c) 2024 M. Kajdak. All rights reserved.
####################################################
set(LIBRARY_NAME library_mdc_app_modules_log)

set(APP_HEADERS_DIR ${CMAKE_SOURCE_DIR}/App/inc)

file(GLOB SOURCES
    ${APP_HEADERS_DIR}/modules/log/impl/log.h
    ${APP_HEADERS_DIR}/modules/log/interface.h

    ${CMAKE_CURRENT_SOURCE_DIR}/impl/log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/interface.c
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME}
    PUBLIC ${APP_HEADERS_DIR}
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC library_mdc_app_main
)

