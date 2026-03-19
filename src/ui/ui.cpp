#include "ui.h"
#include <iostream>

#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
  #define SLEEP(ms) Sleep(ms)
#else
  #include <termios.h>
  #include <unistd.h>
  #include <fcntl.h>
  #define SLEEP(ms) usleep((ms) * 1000)

// Non-blocking keyboard hit detection for Unix terminals.
// Temporarily switches the terminal to raw mode and restores it afterward.
static int _kbhit() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) { ungetc(ch, stdin); return 1; }
    return 0;
}

// Single character read without echo for Unix terminals.
static int _getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void hideCursor()      { std::cout << "\033[?25l"; }
void showCursor()      { std::cout << "\033[?25h"; }

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Moves cursor to the top-left corner without erasing content.
// This avoids the flicker caused by a full clear on every frame.
void clearScreenFast() { std::cout << "\033[H"; }

void enableANSI() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode))
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void waitAnyKey() {
    std::cout << "\nPress any key to continue...";
    std::cout.flush();
    while (!_kbhit()) { SLEEP(50); }
    _getch();
}
