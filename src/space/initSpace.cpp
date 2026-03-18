#include "snake/snake.h"
#include "space/space.h"
#include <vector>

const int INITIAL_SNAKE_LEN = 5;

Space::Space(int nRow, int nCol) {
    this->nRow = nRow;
    this->nCol = nCol;

    this->grid.resize(nRow, std::vector<char>(nCol, '.'));

    Snake snake(nRow, nCol);

    this->snake = snake;
}