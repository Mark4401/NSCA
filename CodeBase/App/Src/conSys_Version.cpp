#include"NSCA.h"
#include"Global_Header.h"
#include"Foo.h"

using namespace std;


int main()
{
	WINDOW* Display = Create_Window(1920, 1080, L"NSCA -> Nodal System Components API", true);

	while (System_Events_Queue(true))
	{
		cout << "Active Window\n";
	}

	Delete_User_defined_Window(Display);

	return 0;
}