
# ======================================
# 🟩 Macro: build_prog
# ======================================
# build_prog(name sources headers include_dir sub-folder)
function(build_prog TOOL_NAME BUILD_TYPE SRC_LIST HDR_LIST INCLUDE_DIRS SUBFOLDER LINK_LIBS)
    
    if (BUILD_TYPE STREQUAL "exe")
        add_executable(${TOOL_NAME} ${SRC_LIST} ${HDR_LIST})
    elseif (BUILD_TYPE STREQUAL "lib")
        add_library(${TOOL_NAME} STATIC ${SRC_LIST} ${HDR_LIST})
    elseif (BUILD_TYPE STREQUAL "dll")
        add_library(${TOOL_NAME} SHARED ${SRC_LIST} ${HDR_LIST})
    else()
        message(FATAL_ERROR "Unknown BUILD_TYPE '${BUILD_TYPE}' for tool '${TOOL_NAME}' (expected 'exe', 'lib', or 'dll')")
    endif()

    target_include_directories(${TOOL_NAME} PRIVATE ${INCLUDE_DIRS})

    if (WIN32)
        target_compile_definitions(${TOOL_NAME} PRIVATE UNICODE _UNICODE)
    endif()

    target_compile_options(${TOOL_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    if (LINK_LIBS)
        target_link_libraries(${TOOL_NAME} PRIVATE ${LINK_LIBS})
    endif()

    set_target_properties(${TOOL_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/${SUBFOLDER}/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/${SUBFOLDER}/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_DIR}/${SUBFOLDER}/$<CONFIG>
    )
endfunction()