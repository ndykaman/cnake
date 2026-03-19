#pragma once

#include "../coordinate/coordinate.h"

// Represents a food item placed on the grid.
// When the snake's head reaches the apple's coordinate, the snake grows
// by `value` segments and a new apple is spawned.
class Apple {
private:
    Coordinate coordinate;
    int        value;

public:
    // Places an apple at (0, 0) with a value of 1.
    Apple();

    // Places an apple at the given grid position with the specified value.
    Apple(int x, int y, int value);

    Coordinate getCoordinate() const;
    int        getValue()      const;
};
