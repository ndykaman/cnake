#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <cstdlib>
#include <vector>

void Snake::move(Direction newDirection) {
    const Coordinate &curHead = this->head;
    const Direction &curDirection = this->direction;
    std::vector<Coordinate> &body = this->body;
    Coordinate newHead;

    if(abs((int)(curDirection) - (int)newDirection) == 2) return;

    switch ((int)newDirection) {
        case 0:
            newHead.x = curHead.x - 1;
            newHead.y = curHead.y;
            break;
        case 1:
            newHead.x = curHead.x;
            newHead.y = curHead.y + 1;
            break;
        case 2:
            newHead.x = curHead.x + 1;
            newHead.y = curHead.y;
            break;
        case 3:
            newHead.x = curHead.x;
            newHead.y = curHead.y - 1;
            break;
    }

    for(int i = this->length - 2; i > 0; i--) {
        body[i] = body[i - 1];
    }

    body[0] = curHead;
    this->head = newHead;
    this->direction = newDirection;
}