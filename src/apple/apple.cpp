#include "apple.h"
#include <random>

Apple::Apple() {
    coordinate = {0, 0};
    value = 1;
}

Apple::Apple(int x, int y, int value) {
    this->value = value;
    coordinate = {x, y};
}

Coordinate Apple::getCoordinate() const {
    return coordinate;
}

int Apple::getValue() const {
    return value;
}