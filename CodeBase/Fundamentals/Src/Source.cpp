#include"Global_Header.h"

using namespace std;

bool Running = true;

void EnableDarkTitleBar(HWND Window_handle)
{
	// NOTE(ME): This Enables the title bar to be fully black and better on the eyes
	BOOL dark_mode = true;
	DwmSetWindowAttribute(Window_handle, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode, sizeof(dark_mode));
	ShowWindow(Window_handle, SW_HIDE);
	ShowWindow(Window_handle, SW_SHOW);
}

LRESULT CALLBACK
MainWindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
		case WM_DESTROY:
		{
			Running = false;

			PostQuitMessage(0);

			break;
		}
	}

	return (Window, Message, WParam, LParam);
}

int WINAPI
wWinMain(HINSTANCE hCurrentInstance, HINSTANCE hPrevInstance, PWSTR pCommandLine, int nCmdShow)
{
	WNDCLASSW PrimaryCLASS = { };

	PrimaryCLASS.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	PrimaryCLASS.lpfnWndProc = MainWindowProc;
	PrimaryCLASS.hInstance = hCurrentInstance;
	PrimaryCLASS.lpszClassName = L"Learning DirectX 11";

	if ( !RegisterClass(&PrimaryCLASS) )
	{
		HWND PrimaryWindow_Handle = CreateWindowExW(
			0,
			PrimaryCLASS.lpszClassName,
			L"My DirectX Window",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT,
			1280, 720,
			NULL, NULL, hCurrentInstance, NULL
		);

		EnableDarkTitleBar( PrimaryWindow_Handle );

		if ( PrimaryWindow_Handle )
		{
			while ( Running )
			{
				MSG MessageLoop;

				while ( PeekMessageW(&MessageLoop, 0, 0, 0, PM_REMOVE) )
				{
					if (MessageLoop.message == WM_QUIT)
					{
						Running = false;
					}
				}

				TranslateMessage(&MessageLoop); // Keyboard message
				DispatchMessageW(&MessageLoop); // Window Handle 
			}
		}
	}
	return 0;
}