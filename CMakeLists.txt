cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CXX_STANDARD 20)

option(NEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO FALSE)

if(NEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO)
    include(chips/arduino-uno-config.cmake)
endif(NEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO)

set(CMAKE_TOOLCHAIN_FILE toolchain/generic-gcc-avr.cmake)
include(${CMAKE_TOOLCHAIN_FILE})

project(NextagEmbeddedPlatform)

add_avr_executable(Test main.cpp)