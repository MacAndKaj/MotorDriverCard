#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.18)

if (NOT DEFINED TESTS)
    # specify cross compilers and tools
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
    set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
    set(CMAKE_AR arm-none-eabi-ar)
    set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
    set(CMAKE_OBJDUMP arm-none-eabi-objdump)
    set(SIZE arm-none-eabi-size)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

    project(MotorDriverCard C ASM)
    set(CMAKE_C_STANDARD 11)

    #Uncomment for hardware floating point
    #add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
    #add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
    #add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

    #Uncomment for software floating point
    #add_compile_options(-mfloat-abi=soft)

    add_compile_options(-mcpu=cortex-m0 -mthumb -mthumb-interwork)
    add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

    # uncomment to mitigate c++17 absolute addresses warnings
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

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

    include_directories(./Inc
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Inc
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy
        ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/include
        ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
        ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0
        ${STM32_REPO_LOCATION}/Drivers/CMSIS/Device/ST/STM32F0xx/Include
        ${STM32_REPO_LOCATION}/Drivers/CMSIS/Include
    )

    add_definitions(-DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG)

    file(GLOB_RECURSE PROJECT_SOURCES 
        "./startup/*.*" 
        "./Src/*.*"
    )

    file(GLOB HAL_SOURCES
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_exti.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c;
        ${STM32_REPO_LOCATION}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.c;
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
        ${STM32_REPO_LOCATION}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c;
    )

    set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F072RBTX_FLASH.ld)

    add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
    add_link_options(-mcpu=cortex-m0 -mthumb -mthumb-interwork)
    add_link_options(-T ${LINKER_SCRIPT})

    add_executable(${PROJECT_NAME}.elf ${PROJECT_SOURCES} ${HAL_SOURCES} ${CMSIS_SOURCES} ${LINKER_SCRIPT})

    set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
            COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
            COMMENT "Building ${HEX_FILE}
    Building ${BIN_FILE}")

else ()
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)

    project(MotorDriverCard C ASM)
    set(CMAKE_C_STANDARD 11)

    message(STATUS "Building tests for MDC.")

    include_directories(./Inc
#            ${STM32_REPO_LOCATION}/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.3/Drivers/STM32F0xx_HAL_Driver/Inc
#            ${STM32_REPO_LOCATION}/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.3/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy
#            ${STM32_REPO_LOCATION}/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.3/Middlewares/Third_Party/FreeRTOS/Source/include
#            ${STM32_REPO_LOCATION}/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.3/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
#            ${STM32_REPO_LOCATION}/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.3/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0
#            ${STM32_REPO_LOCATION}/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.3/Drivers/CMSIS/Device/ST/STM32F0xx/Include
#            ${STM32_REPO_LOCATION}/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.3/Drivers/CMSIS/Include
    )
    add_definitions(-DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG)

    file(GLOB_RECURSE SOURCES
#        "./Src/MDC/*.*"
        "./Src/msg/*.*")

    add_subdirectory(test)
endif()