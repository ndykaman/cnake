#pragma once

#include "../apple/apple.h"
#include "../direction/direction.h"
#include "../snake/snake.h"
#include <vector>

// Owns the game world: the grid, the snake, and the current apple.
// Each game tick, call updateSnake() then render() + print() to advance state.
class Space {
private:
    int                          nRow;
    int                          nCol;
    Snake                        snake;
    Apple                        apple;
    std::vector<std::vector<char>> grid;

    // Chooses a random empty cell and places a new apple there.
    void spawnApple();

public:
    Space(int nRow, int nCol);

    // Moves the snake in `newDirection`, handles apple consumption and self-collision.
    void updateSnake(Direction newDirection);

    // Writes the current game state into the internal character grid.
    void render();

    // Prints the character grid to stdout, one row per line.
    void print() const;

    // Returns true while the snake has not collided with itself.
    bool isSnakeAlive() const;

    // Returns the player's current score (snake length minus initial length).
    int getScore() const;

    // Returns current snake's length
    int getSnakeLength() const;
};
