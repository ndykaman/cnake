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



