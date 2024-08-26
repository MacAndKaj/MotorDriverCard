####################################################
# Copyright (c) 2024 M. Kajdak. All rights reserved.
####################################################
set(LIBRARY_NAME library_mdc_app_modules_syscom)

set(APP_HEADERS_DIR ${CMAKE_SOURCE_DIR}/App/inc)

file(GLOB SOURCES
    ${APP_HEADERS_DIR}/modules/syscom/interface.h
    ${APP_HEADERS_DIR}/modules/syscom/impl/rx.h
    ${APP_HEADERS_DIR}/modules/syscom/impl/msg_processor.h

    ${CMAKE_CURRENT_SOURCE_DIR}/interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/rx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/msg_processor.c
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME}
    PUBLIC ${APP_HEADERS_DIR}
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC library_os
    PUBLIC library_mdc_app_main
    PUBLIC library_mdc_app_msg
)


