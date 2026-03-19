#pragma once

#include "../space/space.h"

// Runs the main game loop for one play session.
// Handles input polling, state updates, and rendering until the snake dies
// or the player presses 'q'.
// Returns true when the session ends so the caller can return to the menu.
bool runGameLoop(Space& space);
