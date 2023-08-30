add_avr_executable(hello_world
        main.cpp)

avr_target_link_libraries(hello_world PRIVATE NextagEmbeddedPlatform-${AVR_MCU})