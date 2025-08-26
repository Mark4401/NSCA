#include "Internal/NSCA_Platform.h"
#include "NSCA.h"

//void BlackTitleBar(HWND Window_handle)
//{
//	// NOTE(ME): This Enables the title bar to be fully black and better on the eyes
//	BOOL dark_mode = true;
//	DwmSetWindowAttribute(Window_handle, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode, sizeof(dark_mode));
//	ShowWindow(Window_handle, SW_HIDE);
//	ShowWindow(Window_handle, SW_SHOW);
//}

void NSCA_BlackTitleBar(HWND Window_handle)
{
	// NOTE(ME): This Enables the title bar to be fully black and better on the eyes
	BOOL dark_mode = true;
	DwmSetWindowAttribute(Window_handle, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode, sizeof(dark_mode));
	ShowWindow(Window_handle, SW_HIDE);
	ShowWindow(Window_handle, SW_SHOW);
}
