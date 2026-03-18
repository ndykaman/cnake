#pragma once

#include "coordinate/coordinate.h"

class Apple {
private:
    Coordinate coordinate;
    int value;

public:
    Apple();
    Apple(int nRow, int nCol);

    Coordinate getCoordinate() const;
    int getValue() const;
};