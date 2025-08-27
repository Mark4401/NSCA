#ifndef NSCA_PLUS_PLUS_H
#define NSCA_PLUS_PLUS_H
#include "NSCA.h"

namespace NSCA
{
    class Window
    {
    public:
        Window(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar)
        {
            handle = ::Create_Window(Height, Width, App_title, Dark_title_bar);
        }

        ~Window()
        {
            if (handle)
            {
                ::Delete_User_defined_Window(handle);
                handle = nullptr;
            }
        }

        bool PollEvents(bool active = true) const
        {
            return ::System_Events_Queue(active);
        }

        WINDOW* raw() const { return handle; }

        // non-copyable
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        // movable
        Window(Window&& other) noexcept : handle(other.handle)
        {
            other.handle = nullptr;
        }

        Window& operator=(Window&& other) noexcept
        {
            if (this != &other)
            {
                if (handle)
                    ::Delete_User_defined_Window(handle);
                handle = other.handle;
                other.handle = nullptr;
            }
            return *this;
        }

    private:
        WINDOW* handle = nullptr;
    };
}

#endif // !NSCA_PLUS_PLUS_H
