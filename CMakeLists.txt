cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project(DX11_repo VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Global build output directory
# set(GLOBAL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Builds)

# define a global root for all binary outputs
set(GLOBAL_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Builds")

# include the functions file
include(cmake/build_tool.cmake)
include(cmake/lib_build_Script.cmake)

# Add subdirectory app
add_subdirectory(CodeBase/App)
add_subdirectory(CodeBase/DX11_Library)

