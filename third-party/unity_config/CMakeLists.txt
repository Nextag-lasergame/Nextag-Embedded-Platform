add_library(unity-config INTERFACE)

target_include_directories(unity-config
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # For builds
        $<INSTALL_INTERFACE:include>                            # For installs
)

# (Optional) Install rules
install(
        DIRECTORY include/
        DESTINATION include
)
install(
        TARGETS unity-config
        EXPORT unity-configTargets
)
install(
        EXPORT unity-configTargets
        FILE unity-configTargets.cmake
        NAMESPACE unity-config::
        DESTINATION lib/cmake/MyLib
)