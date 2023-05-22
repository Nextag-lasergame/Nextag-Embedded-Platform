add_avr_executable(DigitalIO main.cpp)
avr_target_link_libraries(DigitalIO
        unity::framework
        TestUtils-${AVR_MCU}
        NextagEmbeddedPlatform-${AVR_MCU})

add_test(NAME DigitalIO COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/DigitalIO-${AVR_MCU}.elf ${AVR_MCU} 16000000)
