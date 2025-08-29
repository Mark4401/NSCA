# Nodal System Components API (NSCA)

## Introduction

This project has two primary goals:

1. Develop a **comprehensive platform API** capable of targeting multiple aspects of application development.
2. Strengthen my **C/C++ knowledge, design practices, and technical prowess** through practical implementation.

---

## Project Tools & Configurations

* **CMake**: 3.31.6 (MSVC-6)
* **Programming Languages**: C17, C++23
* **Win32 API**: Core libraries (current focus)



## File Structure

```txt
C-1   /Root
A-1   └─ /Archives
B-1   └─ /Builds
C_-1  └─ /cmake
C_-2  └─ /CodeBase
E-1   └─ /Library_Builds
M-1   └─ /Markdown
```

| Definition Codes  | Path                | Notes                                                          |
| ----- | ------------------- | -------------------------------------------------------------- |
| C-1   | /Root               | **NSCA Project (top-level root)**                              |
| A-1   | └─ /Archives        | Archived builds, docs, or old code                             |
| B-1   | └─ /Builds          | **Note:** only 2 visible subfolders: `/App_dir` & `/NSCA_lib` |
| C\_-1 | └─ /cmake           | CMake modules, presets, and configs                            |
| C\_-2 | └─ /CodeBase        | Main source code                                               |
| E-1   | └─ /Library\_Builds | Compiled libraries and artifacts                               |
| M-1   | └─ /Markdown        | Documentation and notes (Markdown format)                      |

---
## Cmake Breakdown

The primary cmake File : `CMakeLists.txt` at the /root directory `C-1` 
contains the following Variables:

- `GLOBAL_OUTPUT_DIR` -> output path **B-1/** containing either Debug or Release binaries.
- `EXTERNAL_LIBRARIES` -> input path **E-1/**. On previous version it contained v0.2.1 of my NSCA library files & configuration files. Now only containing `DX11 v0.1` winch only provided 
an enable black title bar function at the time.
- `NSCA_BUILD_ROOT` -> output directory for NSCA binaries (.lib, .dll, and .cnake files) followed either by the type of x64 compile configuration.

- `NSCA_PREFIX` -> just context switch for wither /debug or /release paths

- an `list()` function contain any .dll and cmake.config files to copy the dll at the path of an .exe if not added to the `windows system path/`.

- Inclusion of **C_-1/** helper functions for speeding up set-up environment & skip the usual Cmake boilerplate code:
`App_Builder.cmake`,`build_library.cmake`, `DeployDLL.cmake` 

- And  addition of subDirectory folder `/App_Dir` & `/NSCA_lib`

### - Cmake Helper function breakdown

- **App_Builder.cmake:** example of the current use of the function. v0.3

```cmake
cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project(NSCA_app VERSION 0.3 LANGUAGES C CXX)

# Extend CMake's package search paths with the NSCA installation prefix.
# This allows find_package(NSCA) to locate the library correctly.
list(APPEND CMAKE_PREFIX_PATH "${NSCA_PREFIX}")

# Locate the NSCA library. REQUIRED ensures configuration fails if it's not found.
find_package(NSCA REQUIRED)

# ------------------------
# Source and header definitions
# ------------------------

# APP_SRCS: list of C++ source files to be compiled into the application.
set(APP_SRCS    
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/conSys_Version.cpp"
)

# APP_HDRS: header files associated with the project. Useful for IDE integration
# and dependency tracking. Not compiled directly.
set(APP_HDRS
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/Global_Header.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Internal/foo.h"
)

# ------------------------
# Build the application
# ------------------------

# App_builder: custom helper function that creates an executable target
# and configures its build properties.
# Arguments:
#   OUTPUT_DIR        - directory to place the built executable
#   WIN32             - set to OFF to indicate console app (ON for Win32 GUI)
#   EXPORT_FLAG       - optional export macro for symbol visibility (empty here)
#   SOURCES           - list of source files to compile
#   HEADERS           - list of header files for IDE integration
#   PUBLIC_INCLUDES   - include paths propagated to consumers of the target
#   PRIVATE_INCLUDES  - include paths only used internally by this target
#   LINK_LIBS         - external libraries to link against
App_builder(${PROJECT_NAME}
    OUTPUT_DIR           app_dir
    WIN32                OFF
    EXPORT_FLAG          ""
    SOURCES              ${APP_SRCS}
    HEADERS              ${APP_HDRS}
    PUBLIC_INCLUDES      "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    PRIVATE_INCLUDES     "${CMAKE_CURRENT_SOURCE_DIR}/Internal"
    LINK_LIBS            ws2_32 NSCA::NSCA
)

# ------------------------
# Deploy the NSCA DLL
# ------------------------

# deploy_dll: helper function that copies a DLL into the output directory
# of the executable so it can run without additional configuration.
# Arguments:
#   NSCA              - target DLL to deploy
#   "${NSCA_PREFIX}/bin" - source directory of the DLL
#   ${PROJECT_NAME}   - executable target that depends on this DLL
deploy_dll(NSCA "${NSCA_PREFIX}/bin" ${PROJECT_NAME})

```

- **build_library.cmake:** example of the current use of the function. v0.3

```cmake
# ------------------------
# Sources and headers for the NSCA library
# ------------------------

# LIBRARY_SRCS: list of C++ source files to compile into the library.
# Includes both the core NSCA.cpp and NSCA++.cpp files.
set(LIBRARY_SRCS
    # Core library implementation files
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/NSCA.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/NSCA++.cpp"
)

# LIBRARY_HDRS: header files associated with the library.
# These are used for IDE integration, public API exposure, and dependency tracking.
set(LIBRARY_HDRS
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/NSCA.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/NSCA++.h"
)

# ------------------------
# Build and export the NSCA library
# ------------------------

# build_and_export_library: custom helper function to create a library target,
# set its build properties, and optionally generate export symbols for DLLs.
# Arguments:
#   OUTPUT_DIR        - directory where the compiled library will be placed
#   VERSION           - library version number
#   EXPORT_FLAG       - macro for controlling symbol visibility when building DLLs
#   SOURCES           - source files to compile into the library
#   HEADERS           - header files associated with the library
#   LINK_LIBS         - external libraries the library depends on (link-time)
#   PUBLIC_INCLUDES   - include paths exposed to consumers of the library
#   PRIVATE_INCLUDES  - include paths used internally, not exposed externally
build_and_export_library(NSCA
  OUTPUT_DIR       NSCA_Lib
  VERSION          0.2.1
  EXPORT_FLAG      NSCA_EXPORTS
  SOURCES          ${LIBRARY_SRCS}
  HEADERS          ${LIBRARY_HDRS}
  LINK_LIBS        d3d11 dxgi d3dcompiler dwmapi
  PUBLIC_INCLUDES  ${CMAKE_CURRENT_SOURCE_DIR}/Include
  PRIVATE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

```

---

# NSCA Library High-Level Overview: What It Provides

The NSCA library currently exposes functionality in **two styles**:

1. **C-style functional API**
2. **C++ object-oriented API**

Both let you create windows, handle system events, and clean up resources.

### 1. Functional C-Style method

Use **plain functions** to create and manage windows:

| Function                     | What it Does                                                                                       |
| ---------------------------- | -------------------------------------------------------------------------------------------------- |
| `Create_Window`              | Creates a window. Give width, height, title, and fullscreen flag. Returns a pointer to a `WINDOW`. |
| `System_Events_Queue`        | Handles input/events. Call in a loop. Returns `true` while window is active.                       |
| `Delete_User_defined_Window` | Destroys a window and frees memory.                                                                |

**Example:**

```c
WINDOW* Display = Create_Window(1280, 720, L"NSCA Window", true);

while (System_Events_Queue(true))
{
    // Window is active
}

Delete_User_defined_Window(Display);
```

---

### 2. C++ Object-Oriented method

Use the **`NSCA::Window` class** to manage windows more easily:

| Class / Method | What it Does                                                                       |
| -------------- | ---------------------------------------------------------------------------------- |
| `NSCA::Window` | Constructor creates a window. Width, height, title, fullscreen.                    |
| `PollEvents()` | Handles input/events. Returns `true` while window is active.                       |
| Destructor     | Automatically closes window and cleans up resources when object goes out of scope. |

**Example:**

```cpp
NSCA::Window window(600, 800, L"Cpp Wrapper Window", true);

while (window.PollEvents())
{
    // Window is active
}
```

---

explore the files within this repo for more insight into how the library works underneath the hood. 

that's it for me for now. 
（￣︶￣）↗　