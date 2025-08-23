#ifndef NSCA_PLATFROM_H
#define NSCA_PLATFROM_H

// Winsock Library tools 
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <dwmapi.h>
#include <d3d11.h>         // Main Direct3D 11 API
#include <dxgi.h>          // DXGI (swap chain, adapters)
#include <d3dcompiler.h>   // Shader compilation (optional, needed if compiling HLSL at runtime)
#include <DirectXMath.h>  // Optional, but handy for math

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dwmapi.lib")

// Enable Unicode for Win32 API
#ifndef UNICODE
#define UNICODE
#endif 

#endif // !NSCA_PLATFROM_H
