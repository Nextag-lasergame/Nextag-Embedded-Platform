add_subdirectory(unity-avr)
add_subdirectory(unity_config)

target_link_libraries(unity PUBLIC unity-config)
target_compile_options(unity PRIVATE -mmcu=${AVR_MCU})
target_link_options(unity PRIVATE -mmcu=${AVR_MCU})
target_compile_definitions(unity PUBLIC UNITY_INCLUDE_CONFIG_H)
