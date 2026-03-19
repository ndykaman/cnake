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
    while (true) {
        clearScreen();

        std::cout << "\033[1;32m" << BANNER << "\033[0m\n";
        std::cout << "========================================\n";
        std::cout << "           CNAKE DEMO v0.1              \n";
        std::cout << "          Author: Andhika R.            \n";
        std::cout << "========================================\n\n";

        std::cout << "Select an option:\n";
        std::cout << "  1. Play\n";
        std::cout << "  2. Exit\n";
        std::cout << "\nEnter choice (1-2): ";

        char choice;
        std::cin >> choice;

        if (choice == '1') return true;
        if (choice == '2') return false;
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
