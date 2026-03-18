/*

Just for your information, in the code in this section, I asked ChatGPT for help with a cross-platform screen-clearing function.

*/

#include "ui.h"

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define OS_WINDOWS
#else
#include <unistd.h>
#define OS_UNIX
#endif

void clearScreen() {
#ifdef OS_WINDOWS
    static HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    static CONSOLE_SCREEN_BUFFER_INFO csbi;
    static DWORD cellCount;
    static DWORD count;
    static COORD homeCoords = {0, 0};
    static bool initDone = false;

    if (!initDone) {
        if (hOut == INVALID_HANDLE_VALUE) return;
        if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        initDone = true;
    }

    FillConsoleOutputCharacter(hOut, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hOut, homeCoords);

#else
    std::cout << "\033[2J\033[H" << std::flush;
#endif
}