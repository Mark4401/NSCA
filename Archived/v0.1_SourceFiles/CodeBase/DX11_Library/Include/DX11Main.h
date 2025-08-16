#ifndef DX11_MAIN_H
#define DX11_MAIN_H

#ifdef DX11UTILS_EXPORTS
#define DX11UTILS_API __declspec(dllexport)
#else
#define DX11UTILS_API __declspec(dllimport)
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
    DX11UTILS_API void DX11Utils_BlackTitleBar(HWND Window_handle);

#ifdef __cplusplus
} // extern "C"

// C++ wrapper namespace
namespace DX11Utils {
    inline void BlackTitleBar(HWND Window_handle) {
        DX11Utils_BlackTitleBar(Window_handle);
    }
}
#endif // __cplusplus

#endif // DX11_MAIN_H
