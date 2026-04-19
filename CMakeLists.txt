cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_micro_ros C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(PROJECT_NAME_LEFT_ARM ${PROJECT_NAME}_left_arm)
set(PROJECT_NAME_RIGHT_ARM ${PROJECT_NAME}_right_arm)
set(PROJECT_NAME_TORSO ${PROJECT_NAME}_torso)

pico_sdk_init()

link_directories(libmicroros)

set(SOURCE_FILE
    src/main.c
    src/ros.c
    src/debug.c
    src/init.c

    src/joint.c
    src/board.c
    src/sensor.c
    src/pico_uart_transport/pico_uart_transport.c
)

set(LIBRARIES
    pico_stdlib
    microros
    hardware_pwm
    hardware_i2c
    hardware_adc
    ws2812_leds
)

add_executable(${PROJECT_NAME_RIGHT_ARM}
    config/config_rp2040_right_arm.c
    ${SOURCE_FILE}
)

add_executable(${PROJECT_NAME_LEFT_ARM}
        config/config_rp2040_left_arm.c
        ${SOURCE_FILE}
)

add_executable(${PROJECT_NAME_TORSO}
        config/config_rp2040_torso_head.c
        ${SOURCE_FILE}
)



target_link_libraries(${PROJECT_NAME_RIGHT_ARM}
        ${LIBRARIES}
)

target_link_libraries(${PROJECT_NAME_LEFT_ARM}
        ${LIBRARIES}
)

target_link_libraries(${PROJECT_NAME_TORSO}
        ${LIBRARIES}
)



target_include_directories(${PROJECT_NAME_RIGHT_ARM} PUBLIC
        include
        libmicroros/include
)


target_include_directories(${PROJECT_NAME_LEFT_ARM} PUBLIC
    include
    libmicroros/include
)

target_include_directories(${PROJECT_NAME_TORSO} PUBLIC
        include
        libmicroros/include
)



SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Configure Pico
pico_enable_stdio_usb(${PROJECT_NAME_RIGHT_ARM} 1)
pico_enable_stdio_usb(${PROJECT_NAME_LEFT_ARM} 1)
pico_enable_stdio_usb(${PROJECT_NAME_TORSO} 1)

pico_enable_stdio_uart(${PROJECT_NAME_RIGHT_ARM} 0)
pico_enable_stdio_uart(${PROJECT_NAME_LEFT_ARM} 0)
pico_enable_stdio_uart(${PROJECT_NAME_TORSO} 0)

add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# Select Arm
target_compile_definitions(${PROJECT_NAME_RIGHT_ARM} PRIVATE USE_RIGHT_ARM)
target_compile_definitions(${PROJECT_NAME_LEFT_ARM} PRIVATE USE_LEFT_ARM)
target_compile_definitions(${PROJECT_NAME_TORSO} PRIVATE USE_TORSO)


# Generate UF2
pico_add_extra_outputs(${PROJECT_NAME_RIGHT_ARM})
pico_add_extra_outputs(${PROJECT_NAME_LEFT_ARM})
pico_add_extra_outputs(${PROJECT_NAME_TORSO})

add_subdirectory(lib/ws2812_leds)
