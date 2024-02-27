add_avr_executable(timer_ctc_with_interrupt
        main.cpp
        interrupts.cpp)

avr_target_link_libraries(timer_ctc_with_interrupt PRIVATE NextagEmbeddedPlatform-${AVR_MCU})