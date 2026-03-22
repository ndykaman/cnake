#include "gameloop/gameloop.h"
#include "menu/menu.h"
#include "space/space.h"
#include "ui/ui.h"

static constexpr int GRID_ROWS = 18;
static constexpr int GRID_COLS = 35;

int main() {
    enableANSI();
    hideCursor();

    while (true) {
        bool play = showStartMenu();
        if (!play) break;

        showControlsScreen();

        Space space(GRID_ROWS, GRID_COLS);
        runGameLoop(space);
    }

    showCursor();
    return 0;
}
