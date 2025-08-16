# DirectX 11 \~ Application & Library Overview

This project marks my first attempt at **graphics programming**.
While I could have started with **OpenGL**, I chose **DirectX 11** for the challenge and to dive straight into a more complex API.

Libraries like **GLFW** or **SDL3** would provide solid window management, but I prefer avoiding extra third-party dependencies where possible — especially for learning the lower-level parts of the stack.

The project is organized into two main sections:

* **App/** — Contains the `.exe` application that renders output via DirectX 11.
* **DX11\_Library/** — Contains the compiled `.lib` and `.dll` files for the reusable DirectX 11 utility library.

---

## CMake \~ Helper Functions & Build Configuration

The **main CMake file** targets versions **3.16 to 3.28** and enforces:

* **C standard:** 17
* **C++ standard:** 23

All compiled binaries are output to:

> `DX11/Builds`

This directory contains `/Debug` and `/RelWithDebInfo` subfolders for **x64** build configurations.

```md
├── Builds/                     # Global output directory
│   ├── App/                     # Application executables
│   │   ├── Debug/
│   │   └── RelWithDebInfo/
│   └── DX11_Lib/                # Shared library outputs
│       ├── Debug/
│       └── RelWithDebInfo/
```

This layout keeps **distinct project targets** — whether standalone applications or modular sub-repositories — neatly separated, while still sharing a unified build directory.

---

### CMake Helper Scripts

Custom `.cmake` helper scripts under the `cmake/` folder streamline build and linking tasks:

* `build_library.cmake` — Common build rules for libraries.
* `build_application.cmake` — Rules for building executable tools.
* `DX11UtilsConfig.cmake` — Allows external projects to link against the `DX11Utils` library without manually specifying paths.

**Example:** `DX11UtilsConfig.cmake`

```cmake
# DX11UtilsConfig.cmake

# Ensure DX11UTILS_ROOT is defined
if(NOT DEFINED DX11UTILS_ROOT)
    message(FATAL_ERROR "DX11UTILS_ROOT must be set before including DX11UtilsConfig.cmake")
endif()

# Add path for find_package compatibility
list(APPEND CMAKE_PREFIX_PATH "${DX11UTILS_ROOT}")

# Resolve absolute config directory
get_filename_component(DX11UTILS_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

# Define imported shared library target
add_library(DX11Utils::DX11Utils SHARED IMPORTED)

# Set library and include paths
set_target_properties(DX11Utils::DX11Utils PROPERTIES
    IMPORTED_LOCATION             "${DX11UTILS_DIR}/DX11Utils.dll"
    IMPORTED_IMPLIB               "${DX11UTILS_DIR}/DX11Utils.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${DX11UTILS_DIR}"
)

# Attach DLL copy to target
function(_dx11utils_attach_dll_copy target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DX11UTILS_DIR}/DX11Utils.dll"
            "$<TARGET_FILE_DIR:${target}>"
    )
endfunction()

# Public link function
function(dx11utils_link target)
    target_link_libraries(${target} PRIVATE DX11Utils::DX11Utils)
    _dx11utils_attach_dll_copy(${target})
endfunction()
```

Variable and function names can be freely adapted to match your naming conventions.

---

## **CMake Helper Functions — Build System Overview**

The project includes two primary helper scripts under the `cmake/` directory:

* **`build_library.cmake`** — Automates building shared libraries (`.dll` + `.lib`).
* **`build_application.cmake`** — Automates building executable applications (`.exe`).

These functions enforce consistent compiler settings, organize output paths, and simplify linking dependencies.

---

### **1. `build_library`**

**Purpose:**
Builds a **shared library** target and routes all outputs into the global build directory structure.

**Usage Example:**

```cmake
build_library(DX11Utils
    OUTPUT_DIR DX11_Lib

    SOURCES
        Src/DX11Main.cpp
        Src/Internal/DX11Platform.h

    HEADERS
        Include/DX11Main.h

    LINK_LIBS
        d3d11
        dxgi
        d3dcompiler
        dwmapi
)
```

**Arguments:**

| Argument     | Type    | Required | Description                                            |
| ------------ | ------- | -------- | ------------------------------------------------------ |
| `OUTPUT_DIR` | Keyword | ✅        | Subfolder under `GLOBAL_OUTPUT_DIR` for build outputs. |
| `SOURCES`    | List    | ✅        | `.cpp` or `.c` source files to compile.                |
| `HEADERS`    | List    | ✅        | Public `.h` or `.hpp` header files.                    |
| `LINK_LIBS`  | List    | ❌        | Libraries to link against.                             |

**Behavior:**

* Creates a **shared library** target (`add_library(... SHARED ...)`).
* Adds public include directory: `<project>/Include`.
* Adds private include directory for internal headers: `<project>/Src/Internal`.
* Applies compiler definitions: `UNICODE`, `_UNICODE`, and `DX11UTILS_EXPORTS`.
* Enforces UTF-8 encoding for MSVC, GCC, and Clang.
* Routes `.dll`, `.lib`, and `.pdb` outputs to:

  ```
  ${GLOBAL_OUTPUT_DIR}/${OUTPUT_DIR}/$<CONFIG>
  ```

---

### **2. `build_application`**

**Purpose:**
Builds an **executable application** target with optional Win32 GUI mode, library linking, and DLL copy automation.

**Usage Example:**

```cmake
set(APP_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/Source.cpp"
)
set(APP_HDRS
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/Global_Header.h"
)

build_application(Window_Setup_template
    OUTPUT_DIR              App
    SOURCES                 "${APP_SRCS}"
    HEADERS                 "${APP_HDRS}"
    LINK_LIBS               ws2_32 DX11Utils
    LIBRARY_PATH            "${GLOBAL_OUTPUT_DIR}/DX11_Lib/RelWithDebInfo"
    BUILD_BINARIES_PATH     "${GLOBAL_OUTPUT_DIR}/DX11_Lib/RelWithDebInfo"
    WIN32                   ON
)
```

**Arguments:**

| Argument              | Type    | Required | Description                                                 |
| --------------------- | ------- | -------- | ----------------------------------------------------------- |
| `OUTPUT_DIR`          | Keyword | ✅        | Subfolder under `GLOBAL_OUTPUT_DIR` for build outputs.      |
| `SOURCES`             | List    | ✅        | `.cpp` or `.c` source files to compile.                     |
| `HEADERS`             | List    | ✅        | `.h` or `.hpp` header files.                                |
| `LINK_LIBS`           | List    | ✅        | Libraries to link against.                                  |
| `LIBRARY_PATH`        | Path    | ❌        | Path to `.lib` files for linking.                           |
| `BUILD_BINARIES_PATH` | Path    | ❌        | Path to `.dll` files to copy post-build.                    |
| `WIN32`               | Bool    | ❌        | If set, builds a Win32 GUI application (no console window). |

**Behavior:**

* Creates executable target (`add_executable`).
* Switches to Win32 GUI mode if `WIN32` is ON.
* Includes headers from `<project>/Include`.
* Applies compiler definitions: `UNICODE` and `_UNICODE`.
* Enforces UTF-8 encoding for MSVC, GCC, and Clang.
* Adds optional library search path via `target_link_directories`.
* Links against specified libraries via `target_link_libraries`.
* If `BUILD_BINARIES_PATH` is set, copies all `.dll` files from that path to the final executable’s output directory after build.
* Routes all outputs into:

  ```
  ${GLOBAL_OUTPUT_DIR}/${OUTPUT_DIR}/$<CONFIG>
  ```

---
