#pragma once

#include "apple/apple.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <vector>

class Space {
private:
    int nRow;
    int nCol;
    Snake snake;
    Apple apple;
    std::vector<std::vector<char>> grid;

    // helper wrap posisi (bisa dipakai kalau perlu)
    int wrap(int value, int mod) const;

public:
    Space(int nRow, int nCol);

    // update snake, handle apple
    void updateSnake(Direction newDirection);

    // spawn apple baru
    void spawnApple();

    // render & print
    void render();
    void print() const;

    // cek ular masih hidup atau tidak
    bool isSnakeAlive();
};