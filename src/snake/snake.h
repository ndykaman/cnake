#pragma once

#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include <vector>

class Snake {
private:
    Coordinate head;
    std::vector<Coordinate> body;
    int length;
    Direction direction;
public:
    Snake(int length, Coordinate head, Direction direction);
    Snake();
    Coordinate getHead();
    std::vector<Coordinate> getBody();
    int getLength();
    Direction getDirection();
    void move(Direction newDirection);
};
