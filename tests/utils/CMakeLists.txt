set(TEST_UTILS_SOURCES src/serial.cpp)
set(TEST_UTILS_HEADERS include/test_utils/serial.h)

add_avr_library(TestUtils ${TEST_UTILS_SOURCES} ${TEST_UTILS_HEADERS})

avr_target_include_directories(TestUtils PUBLIC include)