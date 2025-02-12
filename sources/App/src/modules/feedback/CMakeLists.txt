####################################################
# Copyright (c) 2024 M. Kajdak. All rights reserved.
####################################################
set(LIBRARY_NAME library_mdc_app_modules_feedback)

set(APP_HEADERS_DIR ${CMAKE_SOURCE_DIR}/App/inc)

file(GLOB SOURCES
    ${APP_HEADERS_DIR}/modules/feedback/interface.h
    ${APP_HEADERS_DIR}/modules/feedback/impl/encoder.h
    ${APP_HEADERS_DIR}/modules/feedback/impl/feedback.h

    ${CMAKE_CURRENT_SOURCE_DIR}/interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/encoder.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/feedback.c
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME}
    PUBLIC ${APP_HEADERS_DIR}
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC library_hal_drivers
    PUBLIC library_os
    PUBLIC library_mdc_app_msg
    PUBLIC library_mdc_app_main
)


