#ifndef NSCA_H
#define NSCA_H

#ifdef NSCA_EXPORTS
#define _NSCA_ __declspec(dllexport)
#else
#define _NSCA_ __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C" {
#endif

	typedef struct __UNIVERSAL_MEMORY__ UNIVERSAL_MEMORY;
	typedef struct __WINDOW__			WINDOW;

#define SYSTEM_MEMORY 1;
#define WINDOW_MEMORY 2;


	_NSCA_ WINDOW* Create_Window(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar);
	_NSCA_ void Delete_User_defined_Window(WINDOW* window);
	
	_NSCA_ bool System_Events_Queue(bool Active_state);

	_NSCA_ void System_Info();
#ifdef __cplusplus
}
#endif // __cplusplus



#endif // DX11_MAIN_H
