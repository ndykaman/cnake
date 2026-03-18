#include "coordinate/coordinate.h"
#include "snake/snake.h"

void Snake::eatApple() {
    int &length = this->length;
    const Coordinate &tail = this->body.back();
    const Coordinate &beforeTail = this->body[length - 2];

    int dx = tail.x - beforeTail.x;
    int dy = tail.y - beforeTail.y;

    Coordinate newTail = {
        dx + tail.x,
        dy + tail.y
    };

    length++;
    this->body.push_back(newTail);
}