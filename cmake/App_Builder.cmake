# cmake/build_application.cmake

function(App_builder TARGET_NAME)
    cmake_parse_arguments(
        APP
        ""                                      # no single-letter args
        "OUTPUT_DIR;WIN32;EXPORT_FLAG"          # single-value keywords
        "SOURCES;HEADERS;LINK_LIBS;PUBLIC_INCLUDES;PRIVATE_INCLUDES"
        ${ARGN}
    )

    # pick multi-config vs single-config
    if(CMAKE_CONFIGURATION_TYPES)
        set(CONFIG_NAME "$<CONFIG>")
    else()
        set(CONFIG_NAME "${CMAKE_BUILD_TYPE}")
    endif()

    # where the .exe will live
    set(OUT_DIR "${GLOBAL_OUTPUT_DIR}/${APP_OUTPUT_DIR}/${CONFIG_NAME}")

    # add executable (optionally WIN32 GUI)
    if(APP_WIN32)
        add_executable(${TARGET_NAME} WIN32 ${APP_SOURCES})
    else()
        add_executable(${TARGET_NAME} ${APP_SOURCES})
    endif()

    # IDE visibility: inject headers so VS/Xcode show them
    if(APP_HEADERS)
        target_sources(${TARGET_NAME} PRIVATE ${APP_HEADERS})
        source_group("Header Files" FILES ${APP_HEADERS})
    endif()

    # public & private include paths (BUILD_INTERFACE only)
    target_include_directories(${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${APP_PUBLIC_INCLUDES}>
        PRIVATE
            $<BUILD_INTERFACE:${APP_PRIVATE_INCLUDES}>
    )

    # Unicode export flag + UTF-8 compiler options
    if(APP_EXPORT_FLAG)
        target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE ${APP_EXPORT_FLAG})
    else()
        target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE)
    endif()
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    # link in your libs (imported targets or full paths)
    target_link_libraries(${TARGET_NAME} PRIVATE ${APP_LINK_LIBS})

    # place only the .exe into OUT_DIR
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}
    )
endfunction()