#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "space/space.h"
#include <vector>

void Space::render() {
    std::vector<std::vector<char>> &grid = this->grid;

    for(auto &vc : grid) {
        for(auto &c : vc) {
            c = '.';
        }
    }

    const Coordinate &head = this->snake.getHead();
    const Direction &direction = this->snake.getDirection();

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