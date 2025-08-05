for `Triangle_D3D11_demo_build.cpp` file to work place within any `/Src` folder and reference it in whatever
CMakelietst.txt file within the project structure

```cmake
# declare your sources and headers
set(APP_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/Triangle_D3D11_demo_build.cpp"
)
set(APP_HDRS
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/Global_Header.h"
)

# call the function
build_tool(Window_Setup
    OUTPUT_DIR   Fundamentals         # sub-folder under GLOBAL_OUTPUT_DIR
    SOURCES      "${APP_SRCS}"
    HEADERS      "${APP_HDRS}"
    LINK_LIBS    d3d11 dxgi d3dcompiler ws2_32 dwmapi xaudio2
    WIN32        ON                   # produces a Win32 GUI exe
)

```

then build the application if it opens and shows an red triangle. it means It build correctly.