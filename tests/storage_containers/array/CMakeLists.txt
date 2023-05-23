add_avr_executable(Array main.cpp)
avr_target_link_libraries(Array
        unity::framework
        TestUtils-${AVR_MCU}
        NextagEmbeddedPlatform-${AVR_MCU})

add_test(NAME Array COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/Array-${AVR_MCU}.elf ${AVR_MCU} 16000000)
