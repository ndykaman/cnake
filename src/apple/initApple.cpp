#include "apple/apple.h"
#include <random>

Apple::Apple() {
    this->coordinate = {0, 0};
    this->value = 1;
}

Apple::Apple(int nRow, int nCol) {
    int minX = 0, maxX = nRow - 1;
    int minY = 0, maxY = nCol - 1;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distX(minX, maxX);
    std::uniform_int_distribution<> distY(minY, maxY);

    int x = distX(gen);
    int y = distY(gen);

    this->coordinate = {x, y};

    this->value = 1;
}