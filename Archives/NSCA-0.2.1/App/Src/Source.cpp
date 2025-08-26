#include"Global_Header.h"
#include"NSCA.h"

/// External/Stable library .h files
//#include<Include/DX11Main.h>

using namespace std;

bool Running = true;

LRESULT CALLBACK
MainWindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
		case WM_DESTROY:
		{
			Running = false;

			PostQuitMessage(0);

			return 0;
		}
		case WM_PAINT:
		{
			// Window painting at resize 
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(Window, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(Window, &ps);
		}
		return 0;
	}

	return DefWindowProcW(Window, Message, WParam, LParam);
}

int WINAPI
wWinMain(HINSTANCE hCurrentInstance, HINSTANCE hPrevInstance, PWSTR pCommandLine, int nCmdShow)
{
	WNDCLASSW PrimaryCLASS = { };

	PrimaryCLASS.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	PrimaryCLASS.lpfnWndProc = MainWindowProc;
	PrimaryCLASS.hInstance = hCurrentInstance;
	PrimaryCLASS.lpszClassName = L"Learning DirectX 11";

	if ( RegisterClassW(&PrimaryCLASS) )
	{
		HWND PrimaryWindow_Handle = CreateWindowExW(
			0,
			PrimaryCLASS.lpszClassName,
			L"NSCA -> Nodal System Components API",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			1000, 500,
			500, 500,
			NULL, NULL, hCurrentInstance, NULL
		);

		//DX11Utils::BlackTitleBar(PrimaryWindow_Handle);
		NSCA::BlackTitleBar(PrimaryWindow_Handle);

		if ( PrimaryWindow_Handle )
		{
			while ( Running )
			{
				MSG MessageLoop = { };

				while ( PeekMessageW(&MessageLoop, 0, 0, 0, PM_REMOVE) )
				{
					if (MessageLoop.message == WM_QUIT)
					{
						Running = false;
						break;
					}

					TranslateMessage(&MessageLoop); // Keyboard message
					DispatchMessageW(&MessageLoop); // Window Handle 
				}

			}
		}
	}

	return 0;
}