####################################################
# Copyright (c) 2026 MacAndKaj. All rights reserved.
####################################################
set(LIBRARY_NAME library_mdc_app_modules_scan)

set(APP_HEADERS_DIR ${CMAKE_SOURCE_DIR}/App/inc)

file(GLOB SOURCES
    ${APP_HEADERS_DIR}/modules/scan/interface.h
    ${APP_HEADERS_DIR}/modules/scan/impl/scan.h

    ${CMAKE_CURRENT_SOURCE_DIR}/interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/scan.c
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${APP_HEADERS_DIR}
    ${CMAKE_SOURCE_DIR}/Core/Inc
)

target_link_libraries(${LIBRARY_NAME}
    library_mdc_app_main
)
