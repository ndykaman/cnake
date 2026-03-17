#include "direction/direction.h"
#include "space/space.h"
#include "ui/ui.h"
#include <iostream>

int main() {
    int r, c;

    std::cin >> r >> c;

    Space * space = new Space(r, c);

    char direction;

    do {
        clearScreen();

        space->render();
        space->print();

        std::cout << "\nEnter the direction (w, a, s, d), q to quit: ";

        std::cin >> direction;

        Direction newDirection;

        if(direction == 'w') newDirection = Direction::North;
        else if(direction == 'd') newDirection = Direction::East;
        else if(direction == 's') newDirection = Direction::South;
        else if (direction == 'a') newDirection = Direction::West;
        else if (direction == 'q') break;
        else {
            std::cout << "\nInvalid direction...\n";
            return 0;
        }

        space->moveSnake(newDirection);
    }while (direction != 'q');

    delete space;
    
    return 0;
}