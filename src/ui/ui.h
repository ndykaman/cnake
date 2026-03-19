#pragma once

// Cross-platform helpers for cursor visibility, screen clearing,
// ANSI escape code support, and blocking key-wait.

// Hides the terminal cursor to prevent flickering during rendering.
void hideCursor();

// Restores the terminal cursor to its normal visible state.
void showCursor();

// Clears the entire terminal screen (uses ANSI escape on Unix, system("cls") on Windows).
void clearScreen();

// Fast in-place clear: moves the cursor to (0,0) without erasing previous output.
// Suitable for mid-game redraws where the grid size is fixed.
void clearScreenFast();

// Enables ANSI virtual terminal processing on Windows 10+.
// No-op on Unix systems.
void enableANSI();

// Blocks until the user presses any key.
void waitAnyKey();
