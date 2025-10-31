file(GLOB_RECURSE NEXTAG_TEST_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE NEXTAG_TEST_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

add_avr_library(NextagTest)

target_sources(
        NextagTest-${AVR_MCU}
        PRIVATE ${NEXTAG_TEST_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${NEXTAG_TEST_HEADERS}
)

avr_target_link_libraries(NextagTest PUBLIC unity::framework)