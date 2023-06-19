add_subdirectory(digital_io)

if (NEXTAG_RUN_SERIAL_TEST)
add_subdirectory(serial)
endif (NEXTAG_RUN_SERIAL_TEST)