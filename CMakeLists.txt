cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Werror -Wall -Wextra -Wno-missing-field-initializers -Wno-error=cpp)

option(NEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO FALSE)

if(NEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO)
    include(chips/arduino-uno-config.cmake)
endif(NEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO)

include(toolchain/generic-gcc-avr.cmake)

add_compile_definitions(UNITY_EXCLUDE_FLOAT)

if(WIN32)
    set(PYTHON_EXECUTABLE python)
else()
    set(PYTHON_EXECUTABLE python3)
endif()

project(NextagEmbeddedPlatform)

enable_testing()
set(CTEST_OUTPUT_ON_FAILURE 1)

add_subdirectory(examples)
add_subdirectory(third-party)
add_subdirectory(tests)

configure_file(test_runner.py test_runner.py COPYONLY)

set(NEXTAG_EMBEDDED_PLATFORM_SOURCES
        src/drivers/digital_io.cpp
        src/drivers/digital_io_registers.h
        src/drivers/serial.cpp
        src/drivers/serial_registers.h
        src/drivers/timer8bit.cpp
        src/drivers/timer_registers.h

        src/interrupt/interrupt_registry.cpp)

set(NEXTAG_EMBEDDED_PLATFORM_HEADERS
        include/NextagEmbeddedPlatform/peripherals.h

        include/NextagEmbeddedPlatform/concepts/drivers/timer.h
        include/NextagEmbeddedPlatform/concepts/concepts.h
        include/NextagEmbeddedPlatform/concepts/typetraits.h

        include/NextagEmbeddedPlatform/drivers/digital_io.h
        include/NextagEmbeddedPlatform/drivers/serial.h
        include/NextagEmbeddedPlatform/drivers/timer8bit.h
        include/NextagEmbeddedPlatform/drivers/timer_clock.h
        include/NextagEmbeddedPlatform/drivers/timer_mode.h
        include/NextagEmbeddedPlatform/drivers/timer_result.h

        include/NextagEmbeddedPlatform/interrupt/interrupt_registry.h
        include/NextagEmbeddedPlatform/interrupt/interrupts.h

        include/NextagEmbeddedPlatform/pin_definitions/pin_definitions.h

        include/NextagEmbeddedPlatform/storage_containers/array.h
        include/NextagEmbeddedPlatform/storage_containers/circular_buffer.h
        include/NextagEmbeddedPlatform/storage_containers/generic_data_iterator.h
        )


add_avr_library(NextagEmbeddedPlatform ${NEXTAG_EMBEDDED_PLATFORM_SOURCES} ${NEXTAG_EMBEDDED_PLATFORM_HEADERS})
avr_target_include_directories(NextagEmbeddedPlatform PUBLIC include)
