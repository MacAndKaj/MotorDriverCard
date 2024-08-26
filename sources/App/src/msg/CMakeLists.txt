####################################################
# Copyright (c) 2024 M. Kajdak. All rights reserved.
####################################################
set(LIBRARY_NAME library_mdc_app_msg)

set(APP_HEADERS_DIR ${CMAKE_SOURCE_DIR}/App/inc)

file(GLOB SOURCES
    # HEADERS
    ${APP_HEADERS_DIR}/msg/defs/Frame.h
    ${APP_HEADERS_DIR}/msg/defs/Message.h
    ${APP_HEADERS_DIR}/msg/defs/PlatformSetMotorPwmValue.h
    ${APP_HEADERS_DIR}/msg/defs/PlatformSetMotorSpeed.h
    ${APP_HEADERS_DIR}/msg/deserializers/PlatformSetMotorPwmValue.h
    ${APP_HEADERS_DIR}/msg/deserializers/PlatformSetMotorSpeed.h
    ${APP_HEADERS_DIR}/msg/serializers/PlatformSetMotorSpeed.h
    ${APP_HEADERS_DIR}/msg/consts.h
    ${APP_HEADERS_DIR}/msg/message_ids.h

    # SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/deserializers/PlatformSetMotorPwmValue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/deserializers/PlatformSetMotorSpeed.c
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers/PlatformSetMotorSpeed.c
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME}
    PUBLIC ${APP_HEADERS_DIR}
)

