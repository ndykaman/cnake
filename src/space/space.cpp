#include "space.h"

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