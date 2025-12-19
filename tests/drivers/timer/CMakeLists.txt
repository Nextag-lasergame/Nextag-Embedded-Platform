add_avr_executable(Timer0Test
        main.cpp
        timer0_tests.cpp)

add_avr_executable(Timer1Test
        main.cpp
        timer1_tests.cpp)

avr_target_link_libraries(Timer0Test
        unity::framework
        NextagTest-${AVR_MCU}
        NextagEmbeddedPlatform-${AVR_MCU})

avr_target_link_libraries(Timer1Test
        unity::framework
        NextagTest-${AVR_MCU}
        NextagEmbeddedPlatform-${AVR_MCU})

add_test(NAME Timer0Test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/Timer0Test-${AVR_MCU}.elf ${AVR_MCU} 16000000)
add_test(NAME Timer1Test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/Timer1Test-${AVR_MCU}.elf ${AVR_MCU} 16000000)
