add_avr_executable(Timer main.cpp)
avr_target_link_libraries(Timer
        unity::framework
        TestUtils-${AVR_MCU}
        NextagEmbeddedPlatform-${AVR_MCU})

add_test(NAME Timer COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/Timer-${AVR_MCU}.elf ${AVR_MCU} 16000000)
