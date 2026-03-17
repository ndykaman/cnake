#pragma once

#include <vector>

class Space {
private:
    std::vector<std::vector<char>> grid;
    int nRow;
    int nCol;
public:
    Space(int nRow, int nCol);
    void print();
};