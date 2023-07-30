add_avr_executable(send_single_bytes
        main.cpp)

avr_target_link_libraries(send_single_bytes PRIVATE NextagEmbeddedPlatform-${AVR_MCU})