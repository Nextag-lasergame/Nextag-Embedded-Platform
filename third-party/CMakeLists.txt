add_subdirectory(unity)

target_compile_options(unity PRIVATE -mmcu=${AVR_MCU})
target_link_options(unity PRIVATE -mmcu=${AVR_MCU})

add_avr_library(avr-libstdcpp
        avr-libstdcpp/src/functexcept.cc
        avr-libstdcpp/src/hash_bytes.cc
        avr-libstdcpp/src/hashtable-aux.h
        avr-libstdcpp/src/hashtable_c++0x.cc
        avr-libstdcpp/src/limits.cc
        avr-libstdcpp/src/list.cc
        avr-libstdcpp/src/math.cc
        avr-libstdcpp/src/new_handler.cc
        avr-libstdcpp/src/tree.cc
)

avr_target_include_directories(avr-libstdcpp
    PUBLIC
        avr-libstdcpp/include
    PRIVATE
        avr-libstdcpp/src
)