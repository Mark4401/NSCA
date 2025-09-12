#include "Global_Header.h"
#include "NSCA.h"
#include<iostream>
#include "C_CPP_test.h"

using namespace std;

//SYSTEM_DATA Data; 

int main(int argc, char* argv[])
{
    WINDOW* Display = Create_Window(1280, 720, L"NSCA -> Nodal System Components API", true);

    Signal_Type Type;

    while (Event_Process(true, &Type))
    {
        switch (Type)
        {
            case NSCA_SIGNAL_QUIT:              cout << "Quit signal received\n"; break;
            case NSCA_SIGNAL_KEYDOWN:           cout << "Key pressed\n"; break;
            case NSCA_SIGNAL_KEYUP:             cout << "Key released\n"; break;
            case NSCA_SIGNAL_MOUSEMOVE:         cout << "Mouse moved\n"; break;
            case NSCA_SIGNAL_Left_MOUSEDOWN:    cout << "Mouse left button down\n"; break;
            case NSCA_SIGNAL_Left_MOUSEUP:      cout << "Mouse left button up\n"; break;
            default:                            break;
        }
    }

    if (Type == NSCA_SIGNAL_QUIT)
    {
        cout << "Perform cleanup...\n";
    }

    Delete_User_defined_Window(Display);

    System_Info();

    return 0;
}
