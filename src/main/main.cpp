#include "coordinate/coordinate.h"
#include "direction/direction.h"
#include "snake/snake.h"
#include <iostream>

int main() {
    std::cout << "Hello CNAKE!\n";

    Snake * snake = new Snake(5, {3, 6}, Direction::West);

    std::cout << "\n";

    std::cout << "snake length = " << snake->getLength() << "\n";
    std::cout << "snake head = " << snake->getHead().x << " " << snake->getHead().y << "\n";
    std::cout << "snake direction = " << (int)snake->getDirection() << "\n";
    std::cout << "snake body: \n";
    
    for(auto [x,y] : snake->getBody()) {
        std::cout << x << " " << y << "\n";
    }

    delete snake;

    std::cout << "\n";
    return 0;
}