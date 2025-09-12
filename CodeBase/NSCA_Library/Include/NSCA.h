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

/***********************************************************

	*	HARDWARE INFORMATION FUNCTIONS

************************************************************/

	_NSCA_ void System_Info();

/***********************************************************

	*	HARDWARE INFORMATION FUNCTIONS

************************************************************/

/***********************************************************

	*	WIN32 DATA & PROCESSES

************************************************************/

	typedef struct __BINARY_FILE_DATA__ NSCA_BINARY_CREATE;

	typedef enum NSCA_Signal_Type
	{
		NSCA_SIGNAL_NONE = 0,
		NSCA_SIGNAL_QUIT,
		NSCA_SIGNAL_KEYDOWN,
		NSCA_SIGNAL_KEYUP,
		NSCA_SIGNAL_MOUSEMOVE,
		NSCA_SIGNAL_Left_MOUSEDOWN,
		NSCA_SIGNAL_Left_MOUSEUP
	
	} Signal_Type;

	_NSCA_ bool Event_Process(bool Active_state, Signal_Type* Type);

/***********************************************************

	*	WIN32 DATA & PROCESSES

************************************************************/

/***********************************************************

	*	WIN32 WINDOW INFORMATION

************************************************************/

	#define SYSTEM_MEMORY 1
	#define WINDOW_MEMORY 2

	typedef struct _WINDOW_MEMORY_	MEM_WINDOW;
	typedef struct __WINDOW__		WINDOW;

	_NSCA_ WINDOW* Create_Window(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar);

	_NSCA_ void Delete_User_defined_Window(WINDOW* window);
	

/***********************************************************

	*	WIN32 WINDOW INFORMATION

************************************************************/


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DX11_MAIN_H
