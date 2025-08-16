# Nodal System Components API ((NSCAconfig.cmake)

# Allow user to specify DX11Utils root directory
if(NOT DEFINED NSCA_ROOT)
    message(FATAL_ERROR "NSCA_ROOT must be set before including NSCAConfig.cmake")
endif()

# Add path to DX11 library for find_package to work
list(APPEND CMAKE_PREFIX_PATH "${NSCA_ROOT}")

# Get absolute path to this config file
get_filename_component(NSCA_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

# Create imported target
add_library(NSCA::NSCA SHARED IMPORTED)

# Set library paths
set_target_properties(NSCA::NSCA PROPERTIES
    IMPORTED_LOCATION             "${NSCA_DIR}/NSCA.dll"
    IMPORTED_IMPLIB               "${NSCA_DIR}/NSCA.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${NSCA_DIR}"
)

# Function to attach DLL copy to a consumer target
function(_nsca_attach_dll_copy target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${NSCA_DIR}/NSCA.dll"
            "$<TARGET_FILE_DIR:${target}>"
    )
endfunction()

# Public function to link and auto-copy DLL
function(nsca_link target)
    target_link_libraries(${target} PRIVATE NSCA::NSCA)
    _nsca_attach_dll_copy(${target})
endfunction()
