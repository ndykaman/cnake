#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "space/space.h"
#include <cstdlib>

void Space::moveSnake(Direction newDirection) {
    const Coordinate &curHead = this->snake.getHead();
    const Direction &curDirection = this->snake.getDirection();
    const Coordinate &apple = this->apple.getCoordinate();
    Coordinate newHead;

    if(abs((int)(curDirection) - (int)newDirection) == 2) return;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    newHead = {
        curHead.x + dx[(int)newDirection],
        curHead.y + dy[(int)newDirection]
    };

    newHead.x %= nRow;
    newHead.y %= nCol;

    if(newHead.x < 0) newHead.x += nRow;
    if(newHead.y < 0) newHead.y += nCol;

    if(newHead.x == apple.x && newHead.y == apple.y) {
        this->snake.eatApple();
        this->generateRandomApple();
    }

    this->snake.move(this->nRow, this->nCol, newDirection);
}