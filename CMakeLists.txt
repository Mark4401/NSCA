cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project(DX11_repo VERSION 0.1 LANGUAGES C CXX)

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

set(DEBUG_BIN "${GLOBAL_OUTPUT_DIR}/NSCA_Lib/$<CONFIG>/")
set(RELEASE_BIN "${GLOBAL_OUTPUT_DIR}/NSCA_Lib/$<CONFIG>/")


###############################################
###############################################

# Tell CMake where to find the DX11UtilsConfig.cmake
list(APPEND CMAKE_PREFIX_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/libraries/DX11-Version-0-1/"
    "${CMAKE_CURRENT_SOURCE_DIR}/Builds/NSCA_Lib/$<CONFIG>/cmake"
)
    
# External/Stable Library Environment: Variables, Paths, Binaries


set(EXTERNAL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Library_builds")


###############################################
###############################################

find_package(NSCA REQUIRED)

# include the functions file

include(cmake/App_Builder.cmake)
include(cmake/build_library.cmake)
include(cmake/DeployDLL.cmake)

# include(cmake/DX11UtilsConfig.cmake)


# Add subdirectory app
add_subdirectory(CodeBase/App)
add_subdirectory(CodeBase/NSCA_Library)

