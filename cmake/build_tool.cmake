# cmake/build_tool.cmake
function(build_tool TARGET_NAME)
    # parse arguments:
    #   OUTPUT_DIR      : sub-folder under GLOBAL_OUTPUT_DIR
    #   SOURCES         : list of .cpp/.c files
    #   HEADERS         : list of .h/.hpp files
    #   LINK_LIBS       : list of libraries to link
    #   WIN32           : optional flag; set to ON to add WIN32
    cmake_parse_arguments(
        APP
        ""                                         # no single-letter args
        "OUTPUT_DIR;WIN32"                         # keywords
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

    # include, definitions, compile options
    target_include_directories(${TARGET_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    )
    target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE)
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    # link libraries (only on Windows if you like)
    target_link_libraries(${TARGET_NAME} PRIVATE ${APP_LINK_LIBS})

    # route all outputs into the same folder
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${OUT}
        LIBRARY_OUTPUT_DIRECTORY ${OUT}
        RUNTIME_OUTPUT_DIRECTORY ${OUT}
    )
endfunction()
