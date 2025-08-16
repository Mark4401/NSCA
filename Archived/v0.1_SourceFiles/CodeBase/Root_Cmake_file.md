```cmake
cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project(DX11_repo VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# define a global root for all binary outputs

###############################################
###############################################


# Internal Library Environment: Variables, Paths, Binaries



set(GLOBAL_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Builds")

set(DEBUG_BIN "${GLOBAL_OUTPUT_DIR}/DX11_Lib/Debug")
set(RELEASE_BIN "${GLOBAL_OUTPUT_DIR}/DX11_Lib/RelWithDebInfo")


###############################################
###############################################


# External/Stable Library Environment: Variables, Paths, Binaries


set(EXTERNAL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Library_builds")


###############################################
###############################################




# include the functions file
include(cmake/build_applications.cmake)
include(cmake/build_library.cmake)

# include(cmake/DX11UtilsConfig.cmake)


# Add subdirectory app
add_subdirectory(CodeBase/DX11_Library)
add_subdirectory(CodeBase/App)


```