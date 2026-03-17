#include "space/space.h"
#include <iostream>
#include <vector>

void Space::print() {
    const std::vector<std::vector<char>> &grid = this->grid;

    for(auto vc : grid) {
        for(auto c : vc) {
            std::cout << c;
        }
        std::cout << "\n";
    }
}