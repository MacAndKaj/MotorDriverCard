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

file(GLOB CMSIS_SOURCES
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

file(GLOB_RECURSE PROJECT_SOURCES
    "./Core/Src/*.*"
    "./App/src/*.*"
)

add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-T ${LINKER_SCRIPT})

add_executable(${PROJECT_NAME}.elf ${PROJECT_SOURCES} ${HAL_SOURCES} ${CMSIS_SOURCES} ${LINKER_SCRIPT} ${STARTUP_FILE})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
