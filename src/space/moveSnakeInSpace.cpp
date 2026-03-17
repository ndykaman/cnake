#include "direction/direction.h"
#include "space/space.h"

void Space::moveSnake(Direction newDirection) {
    this->snake.move(this->nRow, this->nCol, newDirection);
}