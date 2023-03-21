add_avr_executable(Test main.cpp)
avr_target_link_libraries(Test unity::framework)

add_test(NAME Test COMMAND python ${CMAKE_BINARY_DIR}/test_runner.py ${CMAKE_CURRENT_BINARY_DIR}/Test-${AVR_MCU}.elf)
# add_test(NAME Test123 COMMAND simavr -f 16000000 -m ${AVR_MCU} Test-${AVR_MCU}.elf 2> /dev/null/ | grep OK..)