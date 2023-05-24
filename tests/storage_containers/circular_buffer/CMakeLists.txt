add_avr_executable(CircularBufferTest main.cpp)
avr_target_link_libraries(CircularBufferTest
        unity::framework
        TestUtils-${AVR_MCU}
        NextagEmbeddedPlatform-${AVR_MCU})

add_test(NAME CircularBuffer COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/CircularBufferTest-${AVR_MCU}.elf ${AVR_MCU} 16000000)
