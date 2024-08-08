#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.18)

# specify cross-compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(MotorDriver C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -Wpedantic)

set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/Core/Startup/startup_stm32f303retx.s)
message(STATUS "Startup file used: ${STARTUP_FILE}")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F303RETX_FLASH.ld)
message(STATUS "Linker script used: ${LINKER_SCRIPT}")

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)


#Uncomment for hardware floating point
add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)

add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)

add_link_options(-u _printf_float)

#Uncomment for software floating point
# add_compile_options(-mfloat-abi=soft)

add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-T ${LINKER_SCRIPT})

include_directories(${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/App/inc
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Inc
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/include
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${STM32_REPO_LOCATION}/Drivers/CMSIS/Device/ST/STM32F3xx/Include
    ${STM32_REPO_LOCATION}/Drivers/CMSIS/Include
)

file(GLOB HAL_SOURCES
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c;
    ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c;
)

file(GLOB OS_SOURCES
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/croutine.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/list.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/queue.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/timers.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c;
    ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c;
)

add_library(library_hal_drivers ${HAL_SOURCES})
target_include_directories(library_hal_drivers
    PUBLIC ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy
    PUBLIC ${STM32_REPO_LOCATION}/Drivers/STM32F3xx_HAL_Driver/Inc
)

add_library(library_os ${OS_SOURCES})
target_include_directories(library_os
    PUBLIC ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/include
    PUBLIC ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    PUBLIC ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    PUBLIC ${STM32_REPO_LOCATION}/Drivers/CMSIS/Device/ST/STM32F3xx/Include
    PUBLIC ${STM32_REPO_LOCATION}/Drivers/CMSIS/Include
)

add_subdirectory(App)

set(CORE_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc)
set(CORE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src)

file(GLOB SOURCES
    ${CORE_HEADERS_DIR}/dma.h
    ${CORE_HEADERS_DIR}/FreeRTOSConfig.h
    ${CORE_HEADERS_DIR}/gpio.h
    ${CORE_HEADERS_DIR}/main.h
    ${CORE_HEADERS_DIR}/spi.h
    ${CORE_HEADERS_DIR}/stm32fxx_hal_conf.h
    ${CORE_HEADERS_DIR}/stm32fxx_it.h
    ${CORE_HEADERS_DIR}/tim.h
    ${CORE_HEADERS_DIR}/usart.h

    ${CORE_SOURCE_DIR}/dma.c
    ${CORE_SOURCE_DIR}/freertos.c
    ${CORE_SOURCE_DIR}/gpio.c
    ${CORE_SOURCE_DIR}/main.c
    ${CORE_SOURCE_DIR}/spi.c
    ${CORE_SOURCE_DIR}/stm32fxx_hal_msp.c
    ${CORE_SOURCE_DIR}/stm32fxx_hal_timebase_tim.c
    ${CORE_SOURCE_DIR}/stm32fxx_it.c
    ${CORE_SOURCE_DIR}/syscalls.c
    ${CORE_SOURCE_DIR}/sysmem.c
    ${CORE_SOURCE_DIR}/system_stm32f3xx.c
    ${CORE_SOURCE_DIR}/tim.c
    ${CORE_SOURCE_DIR}/usart.c
)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT} ${STARTUP_FILE})

target_link_libraries(${PROJECT_NAME}.elf
    PUBLIC library_hal_drivers
    PUBLIC library_os
    PUBLIC library_mdc_app_main
    PUBLIC library_mdc_app_msg
    PUBLIC library_mdc_app_modules_controller
    PUBLIC library_mdc_app_modules_feedback
    PUBLIC library_mdc_app_modules_log
    PUBLIC library_mdc_app_modules_syscom
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
