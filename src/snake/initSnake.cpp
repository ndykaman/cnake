#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"

Snake::Snake() {
    this->length = 1;
    this->head = {0, 0};
    this->direction = Direction::East;
}

Snake::Snake(int nRow, int nCol, int length, Coordinate head, Direction direction) {
    this->direction = direction;
    this->head = head;
    this->length = length;

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, -1, 0, 1};

    for(int i = 1; i <= length - 1; i++) {
        int x = head.x + i * dx[(int)direction];
        int y = head.y + i * dy[(int)direction];

        x %= nRow;
        y %= nCol;

        if(x < 0) x += nRow;
        if(y < 0) y += nCol;

        Coordinate body = {x, y};
        
        this->body.push_back(body);
    }
}