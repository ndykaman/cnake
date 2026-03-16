#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <cstdlib>

void Snake::move(Direction newDirection) {
    Coordinate newHead;

    if(abs((int)(this->direction) - (int)newDirection) == 2) return;

    switch ((int)newDirection) {
        case 0:
            newHead.x = this->head.x - 1;
            newHead.y = this->head.y;
            break;
        case 1:
            newHead.x = this->head.x;
            newHead.y = this->head.y + 1;
            break;
        case 2:
            newHead.x = this->head.x + 1;
            newHead.y = this->head.y;
            break;
        case 3:
            newHead.x = this->head.x;
            newHead.y = this->head.y - 1;
            break;
    }

    for(int i = this->length - 2; i > 0; i--) {
        this->body[i] = this->body[i - 1];
    }

    this->body[0] = head;
    this->head = newHead;
    this->direction = newDirection;
}