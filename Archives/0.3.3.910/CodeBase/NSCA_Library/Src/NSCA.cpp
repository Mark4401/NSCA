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

struct KeyBaord_Data
{
	__SYSTEM_DATA__		Data;
	int32_u				Key_Code;
	bool				Key_Cown;
};

struct Mouse_Data
{
	__SYSTEM_DATA__		Data;
	int					X, Y;
	bool				Left_Down;
	bool				Right_Down;
};

// Global pointer to track current window
static WINDOW* g_mainWindow = nullptr;
// Global flag to track if class has been registered
static bool g_classRegistered = false;


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


static NSCA_Signal_Type TranslateMessageType(UINT Message)
{
	switch (Message) {
	case WM_QUIT:        return NSCA_SIGNAL_QUIT;
	case WM_KEYDOWN:     return NSCA_SIGNAL_KEYDOWN;
	case WM_KEYUP:       return NSCA_SIGNAL_KEYUP;
	case WM_MOUSEMOVE:   return NSCA_SIGNAL_MOUSEMOVE;
	case WM_LBUTTONDOWN: return NSCA_SIGNAL_MOUSEDOWN;
	case WM_LBUTTONUP:   return NSCA_SIGNAL_MOUSEUP;
	default:             return NSCA_SIGNAL_NONE;
	}
}


NSCA_Signal_Stream* NSCA_Get_Signal()
{
	NSCA_Signal_Stream* stream = new NSCA_Signal_Stream();
	stream->buffer = nullptr;
	stream->count = 0;
	stream->index = 0;

	__SYSTEM_DATA__* tempBuffer = nullptr;
	int tempCount = 0;

	MSG Message;
	while (PeekMessageW(&Message, 0, 0, 0, PM_REMOVE))
	{

		__SYSTEM_DATA__* newBuffer = new __SYSTEM_DATA__[tempCount + 1];
		for (int i = 0; i < tempCount; ++i)
			newBuffer[i] = tempBuffer[i];

		delete[] tempBuffer;
		tempBuffer = newBuffer;

		// Store current message
		tempBuffer[tempCount].Message = Message.message;
		tempBuffer[tempCount].WParam = Message.wParam;
		tempBuffer[tempCount].LParam = Message.lParam;

		tempCount++;

		TranslateMessage(&Message);
		DispatchMessageW(&Message);
	}

	stream->buffer = tempBuffer;
	stream->count = tempCount;
	stream->index = 0;

	return stream;
}

void NSCA_Release_Signals(NSCA_Signal_Stream* stream)
{
	if (!stream) return;

	if (stream->buffer) {
		delete[] stream->buffer;
		stream->buffer = nullptr;
	}

	delete stream;
}

int NSCA_Stream_Next_Signal(NSCA_Signal_Stream* stream, NSCA_Signal_Type* outType)
{
	if (!stream || !outType || stream->index >= stream->count)
		return 0;

	__SYSTEM_DATA__ sysData = stream->buffer[stream->index++];
	*outType = TranslateMessageType(sysData.Message);

	return 1;
}

int NSCA_Stream_Count(NSCA_Signal_Stream* stream)
{
	if (!stream) return 0;
	return stream->count;
}

WINDOW* Create_Window(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar)
{
	WINDOW* Screen = new __WINDOW__();
	Screen->TypeInfo.ID_type = WINDOW_MEMORY;
	Screen->TypeInfo.memory = nullptr;
	Screen->Height = Height;
	Screen->Width = Width;
	Screen->title = App_title;
	Screen->Dark_title_Bar = Dark_title_bar;

	Screen->hCurrentInstance = GetModuleHandle(nullptr);
	Screen->hPrevInstance = nullptr;
	Screen->pCommandLine = GetCommandLineW();
	Screen->nCmdShow = SW_SHOWDEFAULT;
	Screen->is_Running = true;

	const wchar_t* className = L"NSCA_WindowClass";

	// Register class only once
	if (!g_classRegistered)
	{
		WNDCLASSW Window_CLASS = { };
		Window_CLASS.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		Window_CLASS.lpfnWndProc = MainWindowProc;
		Window_CLASS.hInstance = Screen->hCurrentInstance;
		Window_CLASS.lpszClassName = className;

		if (!RegisterClassW(&Window_CLASS))
		{
			delete Screen;
			cerr << "Window Registration Failed!\n";
			exit(EXIT_FAILURE);
		}

		g_classRegistered = true;
	}

	// Create the window normally
	Screen->Window_handle = CreateWindowExW(
		0,
		className,
		Screen->title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Screen->Height, Screen->Width,
		NULL, NULL, Screen->hCurrentInstance, NULL
	);

	if (!Screen->Window_handle)
	{
		delete Screen;
		cerr << "Window Creation Failed!\n";
		exit(EXIT_FAILURE);
	}

	// Optional dark title bar tweak
	if (Screen->Dark_title_Bar)
		NSCA_BlackTitleBar(Screen->Window_handle);

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

//bool System_Events_Queue(bool Active_state, SYSTEM_DATA* Sys_Data)
//{
//	bool Running = Active_state;
//	MSG MessageLoop = { };
//	
//	SYSTEM_DATA Internal_Data = { };
//
//	while (PeekMessageW(&MessageLoop, 0, 0, 0, PM_REMOVE))
//	{
//		if (MessageLoop.message == WM_QUIT)
//		{
//			Running = false;
//
//			break;
//		}
//
//		TranslateMessage(&MessageLoop); // Keyboard message
//		DispatchMessageW(&MessageLoop); // Window Handle 
//
//		Internal_Data.Message = MessageLoop.message;
//		Internal_Data.WParam = MessageLoop.wParam;
//		Internal_Data.LParam = MessageLoop.lParam;
//	}
//
//	if (Sys_Data)
//	{
//		Sys_Data->Message = Internal_Data.Message;
//		Sys_Data->LParam = Internal_Data.LParam;
//		Sys_Data->WParam = Internal_Data.WParam;
//
//		return Running;
//	}
//
//	std::cout << "System Queue Empty Or Processed All messages!\n";
//
//	return Running;
//}


void System_Info()
{
	// Declare a SYSTEM_INFO structure to hold system information
	SYSTEM_INFO systemInfo;

	// Call GetNativeSystemInfo to populate the structure
	GetNativeSystemInfo(&systemInfo);

	// Display the system information
	std::cout << "\n\n=== System Information ===" << std::endl;

	// Processor architecture
	switch (systemInfo.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		std::cout << "Processor Architecture: x64 (AMD or Intel)" << std::endl;
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		std::cout << "Processor Architecture: ARM" << std::endl;
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		std::cout << "Processor Architecture: Intel Itanium-based" << std::endl;
		break;
	case PROCESSOR_ARCHITECTURE_INTEL:
		std::cout << "Processor Architecture: x86" << std::endl;
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
	default:
		std::cout << "Processor Architecture: Unknown" << std::endl;
		break;
	}

	// Number of processors
	std::cout << "Number of Processors: " << systemInfo.dwNumberOfProcessors << std::endl;

	// Page size
	std::cout << "Page Size: " << systemInfo.dwPageSize << " bytes" << std::endl;

	// Minimum application address
	std::cout << "Minimum Application Address: "
		<< systemInfo.lpMinimumApplicationAddress << std::endl;

	// Maximum application address
	std::cout << "Maximum Application Address: "
		<< systemInfo.lpMaximumApplicationAddress << std::endl;

	// Active processor mask
	std::cout << "Active Processor Mask: 0x"
		<< std::hex << systemInfo.dwActiveProcessorMask << std::dec << std::endl;

	// Processor type
	std::cout << "Processor Type: " << systemInfo.dwProcessorType << std::endl;

	// Allocation granularity
	std::cout << "Allocation Granularity: "
		<< systemInfo.dwAllocationGranularity << " bytes" << std::endl;

	// Processor level
	std::cout << "Processor Level: " << systemInfo.wProcessorLevel << std::endl;

	// Processor revision (split into high/low words for clarity)
	WORD revision = systemInfo.wProcessorRevision;
	std::cout << "Processor Revision: "
		<< HIWORD(revision) << "." << LOWORD(revision) << "\n";
}
