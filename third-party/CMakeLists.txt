add_subdirectory(unity)

target_compile_options(unity PRIVATE -mmcu=${AVR_MCU})
target_link_options(unity PRIVATE -mmcu=${AVR_MCU})