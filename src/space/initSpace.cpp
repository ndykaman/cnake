#include "direction/direction.h"
#include "snake/snake.h"
#include "space/space.h"
#include <vector>
#include <random>

Space::Space(int nRow, int nCol) {
    this->nRow = nRow;
    this->nCol = nCol;

    this->grid.resize(nRow, std::vector<char>(nCol, '.'));

    int minX = 0, maxX = nRow;
    int minY = 0, maxY = nCol;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distX(minX, maxX);
    std::uniform_int_distribution<> distY(minY, maxY);
    std::uniform_int_distribution<> distD(0, 3);

    int x = distX(gen);
    int y = distY(gen);
    int d = distD(gen);

    Snake snake(4, {x, y}, static_cast<Direction>(d));

    this->snake = snake;
}