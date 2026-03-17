#include "space/space.h"
#include <iostream>

int main() {
    int r, c;

    std::cin >> r >> c;

    Space * space = new Space(r, c);

    space->print();

    delete space;
    
    return 0;
}