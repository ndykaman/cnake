#include "space.h"
#include <iostream>

Space::Space(int nRow, int nCol) : nRow(nRow), nCol(nCol), snake(nRow, nCol), apple(nRow, nCol) {
    grid.resize(nRow, std::vector<char>(nCol, '.'));
}

// helper wrap
int Space::wrap(int value, int mod) const {
    value %= mod;
    if (value < 0) value += mod;
    return value;
}

// update snake & handle apple
void Space::updateSnake(Direction newDirection) {
    const Coordinate &curHead = snake.getHead();
    const Coordinate &appleCoord = apple.getCoordinate();
    Coordinate newHead;

    // larang snake balik arah
    if (abs((int)snake.getDirection() - (int)newDirection) == 2) return;

    // arah gerak
    const int DX[4] = {-1, 0, 1, 0};
    const int DY[4] = {0, 1, 0, -1};

    newHead = {
        wrap(curHead.x + DX[(int)newDirection], nRow),
        wrap(curHead.y + DY[(int)newDirection], nCol)
    };

    // makan apel
    if (newHead.x == appleCoord.x && newHead.y == appleCoord.y) {
        snake.eatApple();
        spawnApple();
    }

    // nabrak badan sendiri
    for(auto [x,y] : snake.getBody()) {
        if(newHead.x == x && newHead.y == y) {
            snake.dead();
        }
    }

    snake.move(nRow, nCol, newDirection);
}

// generate apple baru
void Space::spawnApple() {
    apple = Apple(nRow, nCol);
}

// render ke grid internal
void Space::render() {
    // clear grid
    for (auto &row : grid)
        for (auto &c : row) c = '.';

    const Coordinate &head = snake.getHead();
    const Direction &dir = snake.getDirection();
    const Coordinate &appleCoord = apple.getCoordinate();
    const auto &body = snake.getBody();

    // apple
    grid[appleCoord.x][appleCoord.y] = '@';

    // jika ular sudah mati
    if(snake.getStatus() == SnakeStatus::Dead) {
        // head
        grid[head.x][head.y] = '*';

        // body
        for (auto [x, y] : body)
            grid[x][y] = '*';
        
            return;
    }

    // head
    switch ((int)dir) {
        case 0: grid[head.x][head.y] = '^'; break;
        case 1: grid[head.x][head.y] = '>'; break;
        case 2: grid[head.x][head.y] = 'v'; break;
        case 3: grid[head.x][head.y] = '<'; break;
    }

    // body
    for (auto [x, y] : body)
        grid[x][y] = '#';
}

// print ke console
void Space::print() const {
    for (const auto &row : grid) {
        for (const auto &c : row) std::cout << c;
        std::cout << "\n";
    }
}

// cek ular masih hidup atau tidak
bool Space::isSnakeAlive() {
    return snake.getStatus() == SnakeStatus::Alive;
}