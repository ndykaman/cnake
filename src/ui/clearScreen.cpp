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
    std::cout << "\033[H";
#else
    std::cout << "\033[2J\033[H";
#endif
}