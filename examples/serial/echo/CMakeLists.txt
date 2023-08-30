add_avr_executable(serial_echo
        main.cpp)

avr_target_link_libraries(serial_echo PRIVATE NextagEmbeddedPlatform-${AVR_MCU})