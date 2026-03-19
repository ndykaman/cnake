#include "direction/direction.h"
#include "space/space.h"
#include "ui/ui.h"
#include <iostream>
#include <cmath>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#define SLEEP(ms) usleep(ms * 1000)

int _kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int _getch()
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

// ======================= UI =======================
void hideCursor() { std::cout << "\033[?25l"; }
void showCursor() { std::cout << "\033[?25h"; }
void fullClearScreen() { std::cout << "\033[2J\033[H" << std::flush; }

void enableANSI()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode))
        {
            SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }
#endif
}

void waitAnyKey()
{
    std::cout << "\nPress any key to continue...";
    while (!_kbhit()) { SLEEP(50); }
    _getch();
}

// ======================= Input / Game Loop =======================
Direction getInputDirection(Direction currentDir, bool &running)
{
    while (_kbhit())
    {
        char key = _getch();
        Direction inputDir = currentDir;

        if (key == 'w') inputDir = Direction::North;
        else if (key == 'd') inputDir = Direction::East;
        else if (key == 's') inputDir = Direction::South;
        else if (key == 'a') inputDir = Direction::West;
        else if (key == 'q') running = false;

        if (std::abs((int)inputDir - (int)currentDir) != 2)
            currentDir = inputDir;
    }
    return currentDir;
}

bool gameLoop(Space &space)
{
    Direction currentDir = Direction::East;
    bool running = true;

    while (running && space.isSnakeAlive())
    {
        currentDir = getInputDirection(currentDir, running);

        space.updateSnake(currentDir);

        clearScreen();
        space.render();
        space.print();

        SLEEP(150);
    }

    return true; // return ke menu
}

// ======================= Startup Menu =======================
bool showStartMenu()
{
    while (true)
    {
        fullClearScreen();

        // ASCII art CNAKE horizontal
        std::cout << "\033[1;32m"; // hijau terang
        std::cout << R"(
  ____   _   _    _    _  __ _____
 / ___| | \ | |  / \  | |/ /| ____|
| |     |  \| | / _ \ | ' / |  _|
| |___  | |\  |/ ___ \| . \ | |___
 \____| |_| \_/_/   \_\_|\_\|_____|
)" << "\033[0m" << "\n";

        std::cout << "========================================\n";
        std::cout << "           CNAKE DEMO v0.1              \n";
        std::cout << "          Author: Andhika R.            \n";
        std::cout << "========================================\n\n";

        // Menu pilihan
        std::cout << "Select an option:\n";
        std::cout << "1. Play\n";
        std::cout << "2. Exit\n";
        std::cout << "\nEnter choice (1-2): ";

        char choice;
        std::cin >> choice;

        if (choice == '1') return true;
        else if (choice == '2') return false;
    }
}

// ======================= Main =======================
int main()
{
    enableANSI();
    hideCursor();

    bool exitProgram = false;

    while (!exitProgram)
    {
        bool play = showStartMenu();
        if (!play) { exitProgram = true; break; }

        const int rows = 12;
        const int cols = 20;

        // Petunjuk kontrol
        fullClearScreen();
        std::cout << "\033[1;33m"; // kuning terang
        std::cout << "Controls:\n";
        std::cout << "  W = Up\n";
        std::cout << "  A = Left\n";
        std::cout << "  S = Down\n";
        std::cout << "  D = Right\n";
        std::cout << "  Q = Quit (back to menu)\n";
        std::cout << "\033[0m";

        waitAnyKey();
        fullClearScreen();

        Space space(rows, cols);
        gameLoop(space);
    }

    showCursor();
    return 0;
}