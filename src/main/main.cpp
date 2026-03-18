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

    int _kbhit() {
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

        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }

        return 0;
    }

    int _getch() {
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

void hideCursor() {
    std::cout << "\e[?25l";
}

void showCursor() {
    std::cout << "\e[?25h";
}

// ======================= Input =======================

void inputGridSize(int& r, int& c) {
    std::cout << "Enter grid size (rows cols): ";
    std::cin >> r >> c;
}

Direction getInputDirection(Direction currentDir, bool& running) {
    if (!_kbhit()) return currentDir;

    char key = _getch();
    Direction inputDir = currentDir;

    if (key == 'w')      inputDir = Direction::North;
    else if (key == 'd') inputDir = Direction::East;
    else if (key == 's') inputDir = Direction::South;
    else if (key == 'a') inputDir = Direction::West;
    else if (key == 'q') running = false;

    if (std::abs((int)inputDir - (int)currentDir) != 2) {
        return inputDir;
    }

    return currentDir;
}

// ======================= System =======================

void flushInputBuffer() {
#ifdef _WIN32
    while (_kbhit()) _getch();
#else
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif
}

// ======================= Game Loop =======================

void gameLoop(Space& space) {
    Direction currentDir = Direction::East;
    bool running = true;

    while (running) {
        currentDir = getInputDirection(currentDir, running);

        space.updateSnake(currentDir);

        clearScreen();
        space.render();
        space.print();

        flushInputBuffer();
        SLEEP(150);
    }
}

// ======================= Main =======================

int main() {
    hideCursor();

    int r, c;
    inputGridSize(r, c);

    Space space(r, c);

    gameLoop(space);

    showCursor();
    return 0;
}