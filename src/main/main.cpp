#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
    Snake * snake = new Snake(5, {3, 6}, Direction::West);

    std::vector<std::vector<char>> grid(16, std::vector<char>(16, '.'));

    char direction;

    do {
        system("clear");
        std::cout << "\n";

        for(auto &vc : grid) {
            for(auto &c : vc) {
                c = '.';
            }
        }

        grid[snake->getHead().x][snake->getHead().y] = '$';

        for(auto [x,y] : snake->getBody()) {
            grid[x][y] = '#';
        }

        for(auto vc : grid) {
            for(auto c : vc) {
                std::cout << c;
            }
            std::cout << "\n";
        }

        std::cout << "Enter the direction (n, e, s, w), q to quit: ";
        std::cin >> direction;

        Direction newDirection;

        if(direction == 'n') newDirection = Direction::North;
        else if (direction == 'e') newDirection = Direction::East;
        else if(direction == 's') newDirection = Direction::South;
        else if (direction == 'w') newDirection = Direction::West;

        snake->move(newDirection);
    } while(direction != 'q');  

    delete snake;
    
    return 0;
}