#pragma once

#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include <vector>

enum class SnakeStatus {
    Alive,
    Dead
};

class Snake {
private:
    Coordinate head;                      // posisi kepala
    std::vector<Coordinate> body;         // badan (tanpa head)
    Direction direction;                  // arah gerak
    int length;                           // total panjang (head + body)
    SnakeStatus status;                   // status ular

public:
    Snake();
    Snake(int nRow, int nCol);

    int getLength() const;
    Coordinate getHead() const;
    Direction getDirection() const;
    const std::vector<Coordinate>& getBody() const;
    SnakeStatus getStatus() const;

    void move(int nRow, int nCol, Direction newDirection);
    void eatApple();
    void dead();
};