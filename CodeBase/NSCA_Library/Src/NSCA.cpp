#include "Internal/NSCA_Platform.h"
#include "NSCA.h"
#include "NSCA_Platform.h"

using namespace std;

struct __UNIVERSAL_MEMORY__ 
{ 
	/* optional base data */ 
	void* memory;
	int ID_type;
};
struct __WINDOW__ 
{
	__UNIVERSAL_MEMORY__ TypeInfo;
	int Height;
	int Width;
	const wchar_t* title;

	HINSTANCE hCurrentInstance;
	HINSTANCE hPrevInstance;
	PWSTR pCommandLine;
	int nCmdShow;

	HWND Window_handle;

	bool is_Running;
	bool Dark_title_Bar;
};

// Global pointer to track current window
static WINDOW* g_mainWindow = nullptr;

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

void NSCA_BlackTitleBar(HWND Window_handle)
{
	// NOTE(ME): This Enables the title bar to be fully black and better on the eyes
	BOOL dark_mode = true;
	DwmSetWindowAttribute(Window_handle, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode, sizeof(dark_mode));
	ShowWindow(Window_handle, SW_HIDE);
	ShowWindow(Window_handle, SW_SHOW);
}


WINDOW* Create_Window(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar)
{
	WINDOW* Screen						= new __WINDOW__();
	//Screen->TypeInfo.memory				= nullptr;
	Screen->TypeInfo.ID_type			= WINDOW_MEMORY;
	Screen->Height						= Height;
	Screen->Width						= Width;
	Screen->title						= App_title;
	Screen->Dark_title_Bar				= Dark_title_bar;

	//	WIN32 wWinMain Arguments 
	Screen->hCurrentInstance = GetModuleHandle(nullptr);
	Screen->hPrevInstance = nullptr;
	Screen->pCommandLine = GetCommandLineW();
	Screen->nCmdShow = SW_SHOWDEFAULT;
	Screen->is_Running = true;

	const wchar_t* className = L"NSCA_WindowClass";

	WNDCLASSW Window_CLASS = { };

	Window_CLASS.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	Window_CLASS.lpfnWndProc	= MainWindowProc;
	Window_CLASS.hInstance		= Screen->hCurrentInstance;
	Window_CLASS.lpszClassName	= className;

	if ( RegisterClassW(&Window_CLASS) )
	{

		Screen->Window_handle = CreateWindowExW(
			0,
			className,
			Screen->title,
			/*L"NSCA -> Nodal System Components API"*/
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT,
			Screen->Height, Screen->Width,
			NULL, NULL, Screen->hCurrentInstance, NULL
		);
	}
	else
	{
		delete Screen;

		cerr << "Window Registration Failed!\n";

		exit(EXIT_FAILURE);
	}

	// Optional dark title bar tweak
	if (Screen->Dark_title_Bar)
	{
		NSCA_BlackTitleBar(Screen->Window_handle);
	}

	g_mainWindow = Screen; // store reference globally

	return Screen;

}
void Delete_User_defined_Window(WINDOW* window)
{
	if (!window)
		return;

	if (window->Window_handle)
	{
		DestroyWindow(window->Window_handle);
		window->Window_handle = nullptr;
	}

	cout << "Window & values deleted! --> User Event\n";

	delete window; // free heap memory
}


bool System_Events_Queue(bool Active_state)
{
	bool Running = Active_state;
	MSG MessageLoop = { };

	while (PeekMessageW(&MessageLoop, 0, 0, 0, PM_REMOVE))
	{
		if (MessageLoop.message == WM_QUIT)
		{
			Running = false;

			break;
		}

		TranslateMessage(&MessageLoop); // Keyboard message
		DispatchMessageW(&MessageLoop); // Window Handle 
	}

	std::cout << "System Queue Empty Or Processed All messages!\n";

	return Running;
}
