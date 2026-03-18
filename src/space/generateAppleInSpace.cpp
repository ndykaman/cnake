#include "apple/apple.h"
#include "space/space.h"

void Space::generateRandomApple() {
    int nRow = this->nRow;
    int nCol = this->nCol;

    Apple newApple(nRow, nCol);

    this->apple = newApple;
}