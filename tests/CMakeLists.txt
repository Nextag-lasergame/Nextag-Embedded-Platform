add_subdirectory(drivers)
add_subdirectory(utils)

add_avr_executable(Test main.cpp)
avr_target_link_libraries(Test unity::framework)
avr_target_link_libraries(Test TestUtils-atmega328p)

add_test(NAME Test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/Test-${AVR_MCU}.elf ${AVR_MCU} 16000000)
