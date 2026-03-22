#include "menu.h"
#include "../ui/ui.h"
#include <iostream>

#ifdef _WIN32
  #include <conio.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <fcntl.h>

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
#endif

static const char* BANNER = R"(
  ____   _   _    _    _  __ _____
 / ___| | \ | |  / \  | |/ /| ____|
| |     |  \| | / _ \ | ' / |  _|
| |___  | |\  |/ ___ \| . \ | |___
 \____| |_| \_/_/   \_\_|\_\|_____|
)";

bool showStartMenu() {
    int selected = 0; // 0 = Play, 1 = Exit

    while (true) {
        clearScreen();

        std::cout << "\033[1;32m" << BANNER << "\033[0m\n";
        std::cout << "========================================\n";
        std::cout << "   CNAKE v0.1 on ";
        
    #ifdef _WIN32
        std::cout << "Windows";
    #elif defined(__APPLE__) && defined(__MACH__)
        std::cout << "macOS";
    #elif defined(__linux__)
        std::cout << "Linux";
    #else
        std::cout << "Unknown OS";
    #endif

        std::cout << "\n   A Terminal-based Snake Game\n";
        std::cout << "   By Andhika Rahman\n";
        std::cout << "========================================\n\n";

        // ===== MENU =====
        if (selected == 0)
            std::cout << "  \033[4;36m[1] Play\033[0m\n";   // underline + cyan
        else
            std::cout << "  [1] Play\n";

        if (selected == 1)
            std::cout << "  \033[4;36m[2] Exit\033[0m\n";
        else
            std::cout << "  [2] Exit\n";

        // ===== INPUT =====
    #ifdef _WIN32
        char key = _getch();

        if (key == -32) { // arrow key
            key = _getch();
            if (key == 72) selected--; // UP
            if (key == 80) selected++; // DOWN
        } else if (key == '\r') {
            return selected == 0;
        }

    #else
        char key = getchar();

        if (key == '\033') { // escape sequence
            getchar(); // skip '['
            char dir = getchar();

            if (dir == 'A') selected--; // UP
            if (dir == 'B') selected++; // DOWN
        } else if (key == '\n') {
            return selected == 0;
        }
    #endif

        // wrap biar looping
        if (selected < 0) selected = 1;
        if (selected > 1) selected = 0;
    }
}

void showControlsScreen() {
    clearScreen();

    std::cout << "\033[1;33m";
    std::cout << "Controls:\n";
    std::cout << "  W  =  Move Up\n";
    std::cout << "  A  =  Move Left\n";
    std::cout << "  S  =  Move Down\n";
    std::cout << "  D  =  Move Right\n";
    std::cout << "  Q  =  Quit (back to menu)\n";
    std::cout << "\033[0m";

    waitAnyKey();
    clearScreen();
}
