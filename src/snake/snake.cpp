#include "snake.h"
#include <random>

const int INITIAL_SNAKE_LEN = 5;

Snake::Snake() {
    this->length = 1;
    this->head = {0, 0};
    this->direction = Direction::East;
}

Snake::Snake(int nRow, int nCol) {
    this->length = INITIAL_SNAKE_LEN;

    int minX = INITIAL_SNAKE_LEN - 3, maxX = nRow - INITIAL_SNAKE_LEN + 3;
    int minY = INITIAL_SNAKE_LEN - 3, maxY = nCol - INITIAL_SNAKE_LEN + 3;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distX(minX, maxX);
    std::uniform_int_distribution<> distY(minY, maxY);
    std::uniform_int_distribution<> distD(0, 3);

    int x = distX(gen);
    int y = distY(gen);
    int d = distD(gen);

    this->head = {x, y};

    this->direction = static_cast<Direction>(d);

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