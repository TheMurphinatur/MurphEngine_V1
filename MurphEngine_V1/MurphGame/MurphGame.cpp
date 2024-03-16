// MurphGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../MurphGame/GameApplication.h"
#include "../MurphEngine/Source/Middleware/Bleach_New/BleachNew.h"


GameApplication* gMurphGameApplication = nullptr;

int main([[maybe_unused]]int argc,[[maybe_unused]]char* argv[])
{
    BLEACH_INIT_LEAK_DETECTOR();
    gMurphGameApplication = BLEACH_NEW(GameApplication);
    gMurphGameApplication->Main();
    BLEACH_DELETE(gMurphGameApplication);

    BLEACH_DUMP_AND_DESTROY_LEAK_DETECTOR();
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Get`ting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
