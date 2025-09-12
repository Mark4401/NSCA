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
# Global output directories
# ------------------------
set(GLOBAL_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Builds")
set(EXTERNAL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Library_builds")

# ------------------------
# NSCA library paths and version
# ------------------------
set(NSCA_BUILD_ROOT "${GLOBAL_OUTPUT_DIR}/NSCA_Lib")



if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(NSCA_PREFIX "${NSCA_BUILD_ROOT}/Debug")
else()
    set(NSCA_PREFIX "${NSCA_BUILD_ROOT}/Release")
endif()

# ------------------------
# Add subdirectories
# ------------------------
add_subdirectory(App)
add_subdirectory(NSCA_Library)