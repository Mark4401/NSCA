# REFERENCE — Using DX11Utils in Your Project

Add Library to Your Project Folder
Place the DX11Utils.dll, DX11Utils.lib, DX11UtilsConfig.cmake, and public .h files together in a single folder (for example: libraries/DX11-Version-0-1/).

Tell CMake Where to Find It
In your project’s CMakeLists.txt, add this line before find_package:

```cmake
    list(APPEND CMAKE_PREFIX_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/libraries/DX11-Version-0-1/"
    )
```
Find and Link the Package

```cmake
    find_package(DX11Utils REQUIRED)

    dx11utils_link(MyApp)
```

What Happens Automatically

Links your project to DX11Utils.lib.

Copies DX11Utils.dll to your executable’s output folder after build.

Adds the library’s include directory for your headers

--- 

