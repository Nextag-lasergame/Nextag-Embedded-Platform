function(avr_target_link_libraries EXECUTABLE_TARGET)
    if(NOT ARGN)
        message(FATAL_ERROR "Nothing to link to ${EXECUTABLE_TARGET}.")
    endif(NOT ARGN)

    get_target_property(TARGET_LIST ${EXECUTABLE_TARGET} OUTPUT_NAME)

    foreach(TGT ${ARGN})
        if(TARGET ${TGT})
            get_target_property(ARG_NAME ${TGT} OUTPUT_NAME)
            list(APPEND NON_TARGET_LIST ${ARG_NAME})
        else(TARGET ${TGT})
            list(APPEND NON_TARGET_LIST ${TGT})
        endif(TARGET ${TGT})
    endforeach(TGT ${ARGN})

    target_link_libraries(${TARGET_LIST} ${NON_TARGET_LIST})
endfunction(avr_target_link_libraries EXECUTABLE_TARGET)