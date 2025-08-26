#ifndef NSCA_H
#define NSCA_H

#ifdef NSCA_EXPORTS
#define NSCA __declspec(dllexport)
#else
#define NSCA __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C" {
#endif

	typedef struct __UNIVERSAL_MEMORY__ UNIVERSAL_MEMORY;
	typedef struct __WINDOW__			WINDOW;

#define SYSTEM_MEMORY 1;
#define WINDOW_MEMORY 2;


	NSCA WINDOW* Create_Window(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar);
	NSCA void Delete_User_defined_Window(WINDOW* window);
	
	NSCA bool System_Events_Queue(bool Active_state);

#ifdef  __cplusplus
}
#endif // __cplusplus



#endif // DX11_MAIN_H
