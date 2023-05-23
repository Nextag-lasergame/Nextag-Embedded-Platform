cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CXX_STANDARD 20)

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

add_subdirectory(third-party)
add_subdirectory(tests)

configure_file(test_runner.py test_runner.py COPYONLY)

set(NEXTAG_EMBEDDED_PLATFORM_SOURCES
        src/drivers/digital_io.cpp
        src/drivers/digital_io_registers.h)

set(NEXTAG_EMBEDDED_PLATFORM_HEADERS
        include/NextagEmbeddedPlatform/drivers/digital_io.h
        include/NextagEmbeddedPlatform/pin_definitions/pin_definitions.h
        include/NextagEmbeddedPlatform/storage_containers/array.h
        )


add_avr_library(NextagEmbeddedPlatform ${NEXTAG_EMBEDDED_PLATFORM_SOURCES} ${NEXTAG_EMBEDDED_PLATFORM_HEADERS})
avr_target_include_directories(NextagEmbeddedPlatform PUBLIC include)
