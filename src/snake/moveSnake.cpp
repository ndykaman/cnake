#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <cstdlib>
#include <vector>

void Snake::move(int nRow, int nCol, Direction newDirection) {
    const Coordinate &curHead = this->head;
    const Direction &curDirection = this->direction;
    std::vector<Coordinate> &body = this->body;
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

    for(int i = this->length - 2; i > 0; i--) {
        body[i] = body[i - 1];
    }

    body[0] = curHead;
    this->head = newHead;
    this->direction = newDirection;
}