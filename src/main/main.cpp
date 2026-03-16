#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <iostream>

int main() {
    Snake * snake = new Snake(5, {3, 6}, Direction::West);

    int direction;

    do {
        std::cout << "\n";

        std::cout << snake->getHead().x << " " << snake->getHead().y << "\n";

        for(auto [x,y] : snake->getBody()) {
            std::cout << x << " " << y << "\n";
        }

        std::cout << "Enter the direction (N=0, E=1, S=2, W=3), -1 to abort: ";
        std::cin >> direction;

        Direction newDirection = static_cast<Direction>(direction);

        snake->move(newDirection);
    } while(direction != -1);  

    delete snake;
    
    return 0;
}