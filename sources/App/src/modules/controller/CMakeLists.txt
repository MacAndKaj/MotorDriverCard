####################################################
# Copyright (c) 2024 M. Kajdak. All rights reserved.
####################################################
set(LIBRARY_NAME library_mdc_app_modules_controller)

set(APP_HEADERS_DIR ${CMAKE_SOURCE_DIR}/App/inc)

file(GLOB SOURCES
    ${APP_HEADERS_DIR}/modules/controller/interface.h
    ${APP_HEADERS_DIR}/modules/controller/impl/controller.h
    ${APP_HEADERS_DIR}/modules/controller/impl/defs.h
    ${APP_HEADERS_DIR}/modules/controller/impl/message_dispatch.h
    ${APP_HEADERS_DIR}/modules/controller/impl/motor_process.h
    ${APP_HEADERS_DIR}/modules/controller/impl/pid.h

    ${CMAKE_CURRENT_SOURCE_DIR}/interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/defs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/message_dispatch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/motor_process.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/pid.c
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME}
    PUBLIC ${APP_HEADERS_DIR}
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC library_hal_drivers
    PUBLIC library_os
    PUBLIC library_mdc_app_msg
    PUBLIC library_mdc_app_modules_log
    PUBLIC library_mdc_app_main
)


