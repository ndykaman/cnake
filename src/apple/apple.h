#pragma once

#include "coordinate/coordinate.h"

class Apple {
private:
    Coordinate coordinate;
    int value;

public:
    Apple();
    Apple(int x, int y, int value);

    Coordinate getCoordinate() const;
    int getValue() const;
};