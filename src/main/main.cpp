#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <iostream>

int main() {
    Snake * snake = new Snake(5, {3, 6}, Direction::West);

    std::cout << snake->getHead().x << " " << snake->getHead().y << "\n";

    for(auto [x,y] : snake->getBody()) {
        std::cout << x << " " << y << "\n";
    }

    delete snake;
    
    return 0;
}