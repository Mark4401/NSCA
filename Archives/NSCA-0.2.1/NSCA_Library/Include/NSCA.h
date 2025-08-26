#ifndef NSCA_H
#define NSCA_H

#ifdef NSCA_EXPORTS
#define NSCA_API __declspec(dllexport)
#else
#define NSCA_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    // Forward declaration of HWND as opaque pointer for public header
#ifdef _WIN32
    typedef struct HWND__* HWND;
#else
    typedef void* HWND;  // fallback for non-Windows platforms
#endif

    // C-compatible exported function
    NSCA_API void NSCA_BlackTitleBar(HWND Window_handle);

#ifdef __cplusplus
} // extern "C"

// C++ wrapper namespace
namespace NSCA {
    inline void BlackTitleBar(HWND Window_handle) {
        NSCA_BlackTitleBar(Window_handle);
    }
}
#endif // __cplusplus

#endif // DX11_MAIN_H
