#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"

Snake::Snake(int len, Coordinate head, Direction direction) {
    this->direction = direction;
    this->head = head;
    this->len = len;

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    for(int i = 1; 1 <= len - 1; i++) {
        Coordinate body = {head.x + i * dx[(int)direction],
                            head.y + i * dy[(int)direction]};
        
        this->body.push_back(body);
    }
}