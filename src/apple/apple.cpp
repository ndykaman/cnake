#include "apple.h"

Apple::Apple() : coordinate({0, 0}), value(1) {}

Apple::Apple(int x, int y, int value) : coordinate({x, y}), value(value) {}

Coordinate Apple::getCoordinate() const { return coordinate; }
int        Apple::getValue()      const { return value; }
