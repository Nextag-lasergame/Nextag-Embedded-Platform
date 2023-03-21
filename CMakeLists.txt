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

project(NextagEmbeddedPlatform)

enable_testing()
set(CTEST_OUTPUT_ON_FAILURE 1)

add_subdirectory(third-party)
add_subdirectory(tests)

configure_file(test_runner.py test_runner.py COPYONLY)

target_compile_options(unity PRIVATE -mmcu=${AVR_MCU})
target_link_options(unity PRIVATE -mmcu=${AVR_MCU})

add_avr_executable(Main main.cpp)
