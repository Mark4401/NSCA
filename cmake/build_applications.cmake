# cmake/build_application.cmake
function(build_application TARGET_NAME)
    # parse arguments:
    #   OUTPUT_DIR          : sub-folder under GLOBAL_OUTPUT_DIR
    #   SOURCES             : list of .cpp/.c files
    #   HEADERS             : list of .h/.hpp files (project headers)
    #   LINK_LIBS           : list of libraries to link
    #   WIN32               : optional flag; set to ON to add WIN32
    #   LIBRARY_PATH        : optional path to external headers to include (.h files)
    #   BUILD_BINARIES_PATH : optional path containing .lib and .dll files
    cmake_parse_arguments(
        APP
        ""                                         # no single-letter args
        "OUTPUT_DIR;WIN32;LIBRARY_PATH;BUILD_BINARIES_PATH"  # keywords
        "SOURCES;HEADERS;LINK_LIBS"                # multi-value args
        ${ARGN}
    )

    # build directory: GLOBAL_OUTPUT_DIR/<subdir>/$<CONFIG>
    set(OUT ${GLOBAL_OUTPUT_DIR}/${APP_OUTPUT_DIR}/$<CONFIG>)

    # add executable (include WIN32 only if requested)
    if(APP_WIN32)
        add_executable(${TARGET_NAME} WIN32 ${APP_SOURCES} ${APP_HEADERS})
    else()
        add_executable(${TARGET_NAME} ${APP_SOURCES} ${APP_HEADERS})
    endif()

    # include project headers
    target_include_directories(${TARGET_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    )

    # include external headers if LIBRARY_PATH is specified
    if(APP_LIBRARY_PATH)
        target_include_directories(${TARGET_NAME} PRIVATE "${APP_LIBRARY_PATH}")
    endif()

    # compile definitions and options
    target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE)
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    # add library search directory if BUILD_BINARIES_PATH is provided
    if(APP_BUILD_BINARIES_PATH)
        target_link_directories(${TARGET_NAME} PRIVATE "${APP_BUILD_BINARIES_PATH}")
    endif()

    # link specified libraries
    target_link_libraries(${TARGET_NAME} PRIVATE ${APP_LINK_LIBS})

    # copy DLLs from BUILD_BINARIES_PATH post-build
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

    # set output directories for all target artifacts
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${OUT}
        LIBRARY_OUTPUT_DIRECTORY ${OUT}
        RUNTIME_OUTPUT_DIRECTORY ${OUT}
    )
endfunction()
