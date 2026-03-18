#pragma once

#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include <vector>

class Snake {
private:
    int length;
    Coordinate head;
    Direction direction;
    std::vector<Coordinate> body;
public:
    Snake();
    Snake(int nRow, int nCol);

    int getLength();
    Coordinate getHead();
    Direction getDirection();
    std::vector<Coordinate> getBody();

    void move(int nRow, int nCol, Direction newDirection);
    void eatApple();
};


