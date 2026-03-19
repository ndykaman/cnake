#include "snake.h"
#include <random>

const int INITIAL_SNAKE_LEN = 5;

// arah gerak ke depan (movement)
const int MOVE_DX[4] = {-1, 0, 1, 0};
const int MOVE_DY[4] = {0, 1, 0, -1};

// arah kebalikan (untuk nyusun badan awal)
const int BODY_DX[4] = {1, 0, -1, 0};
const int BODY_DY[4] = {0, -1, 0, 1};

// helper wrap biar gak ngulang
int wrap(int value, int mod) {
    value %= mod;
    if (value < 0) value += mod;
    return value;
}

// default constructor
Snake::Snake() {
    length = 1;
    head = {0, 0};
    direction = Direction::East;
    status = SnakeStatus::Alive;
}

// constructor dengan random spawn
Snake::Snake(int nRow, int nCol) {
    length = INITIAL_SNAKE_LEN;

    int minX = INITIAL_SNAKE_LEN - 3;
    int maxX = nRow - INITIAL_SNAKE_LEN + 3;
    int minY = INITIAL_SNAKE_LEN - 3;
    int maxY = nCol - INITIAL_SNAKE_LEN + 3;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distX(minX, maxX);
    std::uniform_int_distribution<> distY(minY, maxY);
    std::uniform_int_distribution<> distD(0, 3);

    int x = distX(gen);
    int y = distY(gen);
    int d = distD(gen);

    head = {x, y};
    direction = static_cast<Direction>(d);
    status = SnakeStatus::Alive;

    // build body ke arah belakang dari head
    for (int i = 1; i < length; i++) {
        int newX = head.x + i * BODY_DX[(int)direction];
        int newY = head.y + i * BODY_DY[(int)direction];

        newX = wrap(newX, nRow);
        newY = wrap(newY, nCol);

        body.push_back({newX, newY});
    }
}

// gerak snake
void Snake::move(int nRow, int nCol, Direction newDirection) {
    Direction curDirection = direction;

    bool isOpposite = abs((int)curDirection - (int)newDirection) == 2;
    if (isOpposite) return;

    Coordinate newHead = {
        head.x + MOVE_DX[(int)newDirection],
        head.y + MOVE_DY[(int)newDirection]
    };

    newHead.x = wrap(newHead.x, nRow);
    newHead.y = wrap(newHead.y, nCol);

    for (int i = length - 2; i > 0; i--) {
        body[i] = body[i - 1];
    }

    body[0] = head;
    head = newHead;
    direction = newDirection;
}

// makan apel → nambah panjang
void Snake::eatApple(Apple apple) {
    const Coordinate &tail = body.back();
    const Coordinate &beforeTail = body[length - 2];

    int dx = tail.x - beforeTail.x;
    int dy = tail.y - beforeTail.y;

    Coordinate newTail = {
        tail.x + dx,
        tail.y + dy
    };

    length += apple.getValue();
    body.push_back(newTail);
}

// mabrak badan sendiri -> dead
void Snake::dead() {
    status = SnakeStatus::Dead;
}

// getter
Coordinate Snake::getHead() const {
    return head;
}

const std::vector<Coordinate>& Snake::getBody() const {
    return body;
}

int Snake::getLength() const {
    return length;
}

Direction Snake::getDirection() const {
    return direction;
}

SnakeStatus Snake::getStatus() const {
    return status;
}