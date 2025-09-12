#ifndef NSCA_H
#define NSCA_H

#ifdef NSCA_EXPORTS
#define _NSCA_ __declspec(dllexport)
#else
#define _NSCA_ __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

	typedef struct __UNIVERSAL_MEMORY__ UNIVERSAL_MEMORY;
	typedef struct __WINDOW__			WINDOW;

	#define SYSTEM_MEMORY 1;
	#define WINDOW_MEMORY 2;

	typedef struct __BINARY_FILE_DATA__ NSCA_BINARY_CREATE;

	typedef enum NSCA_Signal_Type
	{
		NSCA_SIGNAL_NONE = 0,
		NSCA_SIGNAL_QUIT,
		NSCA_SIGNAL_KEYDOWN,
		NSCA_SIGNAL_KEYUP,
		NSCA_SIGNAL_MOUSEMOVE,
		NSCA_SIGNAL_MOUSEDOWN,
		NSCA_SIGNAL_MOUSEUP
	
	} NSCA_Signal_Type;

	typedef struct NSCA_Signal_Stream NSCA_Signal_Stream;

	_NSCA_ NSCA_Signal_Stream* NSCA_Get_Signal();

	_NSCA_ void NSCA_Release_Signals(NSCA_Signal_Stream* stream);

	_NSCA_ int NSCA_Stream_Next_Signal(NSCA_Signal_Stream* stream, NSCA_Signal_Type* outType);

	_NSCA_ int NSCA_Stream_Count(NSCA_Signal_Stream* stream);

	_NSCA_ WINDOW* Create_Window(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar);

	_NSCA_ void Delete_User_defined_Window(WINDOW* window);
	
	//_NSCA_ bool System_Events_Queue(bool Active_state, SYSTEM_DATA* Sys_Data);

	_NSCA_ void System_Info();


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DX11_MAIN_H
