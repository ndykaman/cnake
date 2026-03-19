#include "input.h"
#include <cmath>

#ifdef _WIN32
  #include <conio.h>
  #define SLEEP(ms) Sleep(ms)
#else
  #include <termios.h>
  #include <unistd.h>
  #include <fcntl.h>
  #define SLEEP(ms) usleep((ms) * 1000)

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

Direction pollInput(Direction currentDir, bool& running) {
    while (_kbhit()) {
        char key = static_cast<char>(_getch());

        if      (key == 'w') currentDir = Direction::North;
        else if (key == 'd') currentDir = Direction::East;
        else if (key == 's') currentDir = Direction::South;
        else if (key == 'a') currentDir = Direction::West;
        else if (key == 'q') { running = false; return currentDir; }
    }
    return currentDir;
}
