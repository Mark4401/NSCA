#include "Global_Header.h"
#include "NSCA.h"
#include<iostream>
#include "C_CPP_test.h"

using namespace std;

//SYSTEM_DATA Data; 

int main(int argc, char* argv[])
{
    WINDOW* Display = Create_Window(1280, 720, L"NSCA -> Nodal System Components API", true);

    int running = 1;

    int totalMessagesCaptured = 0;


    while (running)
    {
        NSCA_Signal_Stream* stream = NSCA_Get_Signal();
        NSCA_Signal_Type type;

        while (NSCA_Stream_Next_Signal(stream, &type))
        {
            switch (type)
            {
            case NSCA_SIGNAL_QUIT:        running = 0; break;
            case NSCA_SIGNAL_KEYDOWN:     cout << "Key pressed\n"; break;
            case NSCA_SIGNAL_KEYUP:       cout << "Key released\n"; break;
            case NSCA_SIGNAL_MOUSEMOVE:   cout << "Mouse moved\n"; break;
            case NSCA_SIGNAL_MOUSEDOWN:   cout << "Mouse button down\n"; break;
            case NSCA_SIGNAL_MOUSEUP:     cout << "Mouse button up\n"; break;
            default:                      break;
            }
        }

        totalMessagesCaptured += NSCA_Stream_Count(stream);

        NSCA_Release_Signals(stream);
    }

    cout << "Total messages captured during the app up-time: " << totalMessagesCaptured << "\n";

    Delete_User_defined_Window(Display);

    System_Info();

    return 0;
}
