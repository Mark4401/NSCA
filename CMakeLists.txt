cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(DX11_repo VERSION 0.3 LANGUAGES C CXX)

# ------------------------
# Compiler standards
# ------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ------------------------
# Include helper functions
# ------------------------
include(cmake/App_Builder.cmake)
include(cmake/build_library.cmake)
include(cmake/DeployDLL.cmake)

# ------------------------
# Test Environment - Private ONLY
# ------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Test )

# ------------------------
# Add subdirectories
# ------------------------
add_subdirectory(CodeBase)

