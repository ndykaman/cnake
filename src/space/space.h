#pragma once

#include "direction/direction.h"
#include "snake/snake.h"
#include <vector>

class Space {
private:
    std::vector<std::vector<char>> grid;
    int nRow;
    int nCol;
    Snake snake;
public:
    Space(int nRow, int nCol);
    void render();
    void print();
    void moveSnake(Direction newDirection);
};