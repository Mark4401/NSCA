function(build_tool TARGET_NAME)
    cmake_parse_arguments(
        APP
        ""  # no single-letter args
        "OUTPUT_DIR;WIN32;LIBRARY_PATH;BUILD_BINARIES_PATH"
        "SOURCES;HEADERS;LINK_LIBS"
        ${ARGN}
    )

    set(OUT ${GLOBAL_OUTPUT_DIR}/${APP_OUTPUT_DIR}/$<CONFIG>)

    if(APP_WIN32)
        add_executable(${TARGET_NAME} WIN32 ${APP_SOURCES} ${APP_HEADERS})
    else()
        add_executable(${TARGET_NAME} ${APP_SOURCES} ${APP_HEADERS})
    endif()

    target_include_directories(${TARGET_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    )
    target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE)
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    # If user gave a LIBRARY_PATH, add it as a link directory for .lib files
    if(APP_LIBRARY_PATH)
        target_link_directories(${TARGET_NAME} PRIVATE "${APP_LIBRARY_PATH}")
    endif()

    # Link all the libs specified
    target_link_libraries(${TARGET_NAME} PRIVATE ${APP_LINK_LIBS})

    # If user gave a BUILD_BINARIES_PATH, copy all DLLs from there to the output dir
    if(APP_BUILD_BINARIES_PATH)
        file(GLOB DLLS_TO_COPY "${APP_BUILD_BINARIES_PATH}/*.dll")
        foreach(dll_file IN LISTS DLLS_TO_COPY)
            add_custom_command(
                TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${dll_file}"
                    $<TARGET_FILE_DIR:${TARGET_NAME}>
            )
        endforeach()
    endif()

    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${OUT}
        LIBRARY_OUTPUT_DIRECTORY ${OUT}
        RUNTIME_OUTPUT_DIRECTORY ${OUT}
    )
endfunction()
