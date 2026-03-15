#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <vector>

Coordinate Snake::getHead() {
    return this->head;
}

std::vector<Coordinate> Snake::getBody() {
    return this->body;
}

int Snake::getLength() {
    return this->length;
}

Direction Snake::getDirection() {
    return this->direction;
}