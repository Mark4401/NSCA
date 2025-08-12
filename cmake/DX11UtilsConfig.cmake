# DX11UtilsConfig.cmake

# Allow user to specify DX11Utils root directory
if(NOT DEFINED DX11UTILS_ROOT)
    message(FATAL_ERROR "DX11UTILS_ROOT must be set before including DX11UtilsConfig.cmake")
endif()

# Add path to DX11 library for find_package to work
list(APPEND CMAKE_PREFIX_PATH "${DX11UTILS_ROOT}")

# Get absolute path to this config file
get_filename_component(DX11UTILS_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

# Create imported target
add_library(DX11Utils::DX11Utils SHARED IMPORTED)

# Set library paths
set_target_properties(DX11Utils::DX11Utils PROPERTIES
    IMPORTED_LOCATION             "${DX11UTILS_DIR}/DX11Utils.dll"
    IMPORTED_IMPLIB               "${DX11UTILS_DIR}/DX11Utils.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${DX11UTILS_DIR}"
)

# Function to attach DLL copy to a consumer target
function(_dx11utils_attach_dll_copy target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DX11UTILS_DIR}/DX11Utils.dll"
            "$<TARGET_FILE_DIR:${target}>"
    )
endfunction()

# Public function to link and auto-copy DLL
function(dx11utils_link target)
    target_link_libraries(${target} PRIVATE DX11Utils::DX11Utils)
    _dx11utils_attach_dll_copy(${target})
endfunction()
