#include "direction/direction.h"
#include "space/space.h"

void Space::moveSnake(Direction newDirection) {
    this->snake.move(newDirection);
}