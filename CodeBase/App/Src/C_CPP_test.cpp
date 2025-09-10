#include "Global_Header.h"
#include "NSCA.h"
#include "NSCA++.h"
#include "C_CPP_test.h"

using namespace std;

void C_method()
{
    WINDOW* Display = Create_Window(1280, 720, L"NSCA -> Nodal System Components API", true);

    while (System_Events_Queue(true))
    {
        cout << "C Method Window Active\n";
    }

    Delete_User_defined_Window(Display);
}

void Cpp_Method()
{
    NSCA::Window window(600, 800, L"Cpp Wrapper Window", true);

    while (window.PollEvents())
    {
        cout << "C++ Wrapper Window Active\n";
    }
}

void Exmaple_Onw()
{
    string input;
    bool keepRunning = true;

    while (keepRunning)
    {
        cout << "Select window method to run:\n";
        cout << "1. C method\n";
        cout << "2. C++ wrapper method\n";
        cout << "Enter choice (1 or 2): ";
        getline(cin, input);

        if (input == "1")
        {
            C_method();
        }
        else if (input == "2")
        {
            Cpp_Method();
        }
        else if (input == "Exit" || input == "exit")
        {
            cout << "\nExit Command called\n";
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
            continue;
        }

        cout << "Do you want to run another window? (y/n): ";
        getline(cin, input);

        if (input != "y" && input != "Y")
        {
            keepRunning = false;
        }
    }

    cout << "Program exiting...\n\n";

    System_Info();
}