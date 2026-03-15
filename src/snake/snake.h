#pragma once

#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include <vector>

class Snake {
private:
    Coordinate head;
    std::vector<Coordinate> body;
    int len;
    Direction direction;
public:
    Snake(int len, Coordinate head, Direction direction);
};
