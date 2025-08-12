#include"Global_Header.h"


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
			L"My DirectX Window",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			0, 0,
			1980, 1080,
			NULL, NULL, hCurrentInstance, NULL
		);

		//DX11Utils_BlackTitleBar(PrimaryWindow_Handle);

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