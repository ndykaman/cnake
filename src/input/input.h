#pragma once

#include "../direction/direction.h"

// Drains all pending keystrokes and maps them to a movement direction.
// Updates `running` to false if the quit key ('q') is pressed.
// Ignores any key that would reverse the snake's current direction.
Direction pollInput(Direction currentDir, bool& running);
