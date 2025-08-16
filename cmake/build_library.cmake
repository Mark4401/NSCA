function(build_library TARGET_NAME)
    #   LIB             : parse arguments:
    #   OUTPUT_DIR      : sub-folder under GLOBAL_OUTPUT_DIR
    #   SOURCES         : list of .cpp/.c files
    #   HEADERS         : list of public .h/.hpp files
    #   LINK_LIBS       : list of libraries to link (optional)
    cmake_parse_arguments(
        LIB
        ""                                         # no single-letter args
        "OUTPUT_DIR"                               # keywords
        "SOURCES;HEADERS;LINK_LIBS"                # multi-value args
        ${ARGN}
    )

    # build directory: GLOBAL_OUTPUT_DIR/<subdir>/$<CONFIG>
    set(OUT ${GLOBAL_OUTPUT_DIR}/${LIB_OUTPUT_DIR}/$<CONFIG>)

    # add static library
    add_library(${TARGET_NAME} SHARED ${LIB_SOURCES} ${LIB_HEADERS})

    # public headers
    target_include_directories(${TARGET_NAME}
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Src/Internal"
    )

    # definitions and compile options
    target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE NSCA_EXPORTS)
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    # link libraries (if any)
    if(LIB_LINK_LIBS)
        target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_LINK_LIBS})
    endif()

    # route all outputs into the same folder
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${OUT}
        LIBRARY_OUTPUT_DIRECTORY ${OUT}
        RUNTIME_OUTPUT_DIRECTORY ${OUT}
    )


endfunction()
