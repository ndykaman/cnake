#include "space.h"
#include <iostream>

const int INITIAL_SNAKE_LEN = 5;

Space::Space(int nRow, int nCol) {
    this->nRow = nRow;
    this->nCol = nCol;

    this->grid.resize(nRow, std::vector<char>(nCol, '.'));

    Snake snake(nRow, nCol);

    Apple apple(nRow, nCol);

    this->apple = apple;
    this->snake = snake;
}



void Space::render() {
    std::vector<std::vector<char>> &grid = this->grid;

    for(auto &vc : grid) {
        for(auto &c : vc) {
            c = '.';
        }
    }

    const Coordinate &head = this->snake.getHead();
    const Direction &direction = this->snake.getDirection();
    const Coordinate &apple = this->apple.getCoordinate();

    grid[apple.x][apple.y] = '@';

    switch ((int)direction) {
        case 0:
            grid[head.x][head.y] = '^';
            break;
        case 1:
            grid[head.x][head.y] = '>';
            break;
        case 2:
            grid[head.x][head.y] = 'v';
            break;
        case 3:
            grid[head.x][head.y] = '<';
            break;
    }

    const std::vector<Coordinate> &body = this->snake.getBody();

    for(auto [x,y] : body) {
        grid[x][y] = '#';
    }
}



void Space::print() {
    const std::vector<std::vector<char>> &grid = this->grid;

    for(auto vc : grid) {
        for(auto c : vc) {
            std::cout << c;
        }
        std::cout << "\n";
    }
}



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