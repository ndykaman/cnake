#include "gameloop.h"
#include "../input/input.h"
#include "../ui/ui.h"
#include <iostream>

#ifdef _WIN32
  #include <windows.h>
  #define SLEEP(ms) Sleep(ms)
#else
  #include <unistd.h>
  #define SLEEP(ms) usleep((ms) * 1000)
#endif

static constexpr int TICK_MS         = 150; // Milliseconds between game ticks.
static constexpr int DEATH_LINGER_MS = 3000; // How long to show the death screen.

bool runGameLoop(Space& space) {
    Direction currentDir = Direction::East;
    bool      running    = true;

    while (running) {
        currentDir = pollInput(currentDir, running);

        space.updateSnake(currentDir);

        // Redraw in-place each tick to avoid full-screen flicker.
        clearScreenFast();
        space.render();
        space.print();
        std::cout << "Score: " << space.getScore() << '\n';
        std::cout.flush();

        if (!space.isSnakeAlive()) {
            std::cout << "\nGame over! Final score: " << space.getScore() << '\n';
            SLEEP(DEATH_LINGER_MS);
            break;
        }

        SLEEP(TICK_MS);
    }

    return true;
}
