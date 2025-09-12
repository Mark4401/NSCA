#ifndef NSCA_PLATFROM_H
#define NSCA_PLATFROM_H

// Winsock Library tools 
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// 8-bit
typedef signed char       int8_s;
typedef unsigned char     int8_u;

// 16-bit
typedef signed short      int16_s;
typedef unsigned short    int16_u;

// 32-bit
typedef signed int        int32_s;
typedef unsigned int      int32_u;

// 64-bit
typedef signed long long  int64_s;
typedef unsigned long long int64_u;



/*	USECASE

	int8_s		a = -100;
	int8_u		b = 200;
	int16_s		c = -30000;
	int16_u		d = 60000;
	int32_s		e = -1000000000;
	int32_u		f = 3000000000U;
	int64_s		g = -5000000000LL;
	int64_u		h = 10000000000ULL;

*/


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

#include <string>
#include <iostream>
#include <Windows.h>

typedef struct __SYSTEM_DATA__
{
	UINT    Message;
	WPARAM  WParam;
	LPARAM  LParam;
} __SYSTEM_DATA__;

struct NSCA_Signal_Stream
{
	__SYSTEM_DATA__* buffer;
	int count;
	int index;
};
// Enable Unicode for Win32 API
#ifndef UNICODE
#define UNICODE
#endif 

#endif // !NSCA_PLATFROM_H
