#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
    Snake * snake = new Snake(5, {3, 6}, Direction::West);

    std::vector<std::vector<char>> grid(16, std::vector<char>(16, '.'));

    int direction;

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

        std::cout << "Enter the direction (N=0, E=1, S=2, W=3), -1 to abort: ";
        std::cin >> direction;

        Direction newDirection = static_cast<Direction>(direction);

        snake->move(newDirection);
    } while(direction != -1);  

    delete snake;
    
    return 0;
}