#pragma once

#include "../coordinate/coordinate.h"
#include "../direction/direction.h"
#include "../apple/apple.h"
#include <vector>

// Tracks whether the snake is still in play or has collided with itself.
enum class SnakeStatus {
    Alive,
    Dead
};

// Manages the snake's position, direction, body segments, and growth.
// The head is stored separately from the body for fast head-access.
// Body index 0 is the segment directly behind the head.
class Snake {
private:
    Coordinate              head;
    std::vector<Coordinate> body;
    Direction               direction;
    int                     length;
    SnakeStatus             status;

public:
    // Initialises a minimal snake at (0,0) facing East with length 1.
    Snake();

    // Spawns a snake of INITIAL_SNAKE_LEN at a random position inside
    // the given grid dimensions, facing a random direction.
    Snake(int nRow, int nCol);

    int                          getLength()    const;
    Coordinate                   getHead()      const;
    Direction                    getDirection() const;
    const std::vector<Coordinate>& getBody()    const;
    SnakeStatus                  getStatus()    const;

    // Moves the snake one step in `newDirection`.
    // Ignores the request if `newDirection` is directly opposite the current direction.
    void move(int nRow, int nCol, Direction newDirection);

    // Extends the snake's tail by `apple.getValue()` segments and updates length.
    void grow(const Apple& apple);

    // Marks the snake as dead after a self-collision.
    void kill();
};
