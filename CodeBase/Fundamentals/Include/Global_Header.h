#ifndef APP_ENTRY_H
#define APP_ENTRY_H

// Winsock Library tools 
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// Windows API headers

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <minwinbase.h>
#include <libloaderapi.h>
#include <xinput.h>
#include <dwmapi.h>
#include <d3d11.h>         // Main Direct3D 11 API
#include <dxgi.h>          // DXGI (swap chain, adapters)
#include <d3dcompiler.h>   // Shader compilation (optional, needed if compiling HLSL at runtime)
#include <DirectXMath.h>  // Optional, but handy for math

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// C++ STD Headers

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <format>
#include <cstdint>

#pragma warning(disable : 28251)
/*
	it ignores the stupid _in_ _in_ _out_ _in_ annotation warning for wWinMain Entry point.
*/

// Enable Unicode for Win32 API
#ifndef UNICODE
#define UNICODE
#endif 


#endif // !APP_ENTRY_H
