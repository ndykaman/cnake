#include "space.h"
#include "../utils/utils.h"
#include <iostream>
#include <random>

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"

static constexpr int INITIAL_SNAKE_LEN = 5;

Space::Space(int nRow, int nCol)
    : nRow(nRow), nCol(nCol),
      snake(nRow, nCol), apple(),
      grid(nRow, std::vector<char>(nCol, '.')) {
    spawnApple();
}

void Space::updateSnake(Direction newDirection) {
    if (isOppositeDirection(snake.getDirection(), newDirection)) return;

    // Calculate where the head will land after this move.
    const Coordinate& curHead = snake.getHead();
    Coordinate newHead = {
        wrap(curHead.x + MOVE_DX[(int)newDirection], nRow),
        wrap(curHead.y + MOVE_DY[(int)newDirection], nCol)
    };

    // Check for apple consumption before moving so the tail is still in place.
    const Coordinate& applePos = apple.getCoordinate();
    bool ateApple = (newHead.x == applePos.x && newHead.y == applePos.y);

    // Check for self-collision: the new head must not overlap any body segment.
    for (const auto& [x, y] : snake.getBody()) {
        if (newHead.x == x && newHead.y == y) {
            snake.kill();
            return;
        }
    }

    snake.move(nRow, nCol, newDirection);

    if (ateApple) {
        snake.grow(apple, nRow, nCol);
        spawnApple();
    }
}

void Space::spawnApple() {
    // Collect every cell that is not occupied by the snake, then pick one at random.
    std::vector<Coordinate> emptyCells;
    emptyCells.reserve(nRow * nCol);

    const Coordinate&              head = snake.getHead();
    const std::vector<Coordinate>& body = snake.getBody();

    for (int r = 0; r < nRow; ++r) {
        for (int c = 0; c < nCol; ++c) {
            bool occupied = (r == head.x && c == head.y);
            for (const auto& [bx, by] : body)
                if (r == bx && c == by) { occupied = true; break; }
            if (!occupied) emptyCells.push_back({r, c});
        }
    }

    if (emptyCells.empty()) return; // Grid is completely full — no space for an apple.

    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, (int)emptyCells.size() - 1);
    const Coordinate& chosen = emptyCells[dist(gen)];
    apple = Apple(chosen.x, chosen.y, 1);
}

void Space::render() {
    // Reset every cell to the empty character before drawing game objects.
    for (auto& row : grid)
        for (auto& c : row) c = '.';

    const Coordinate&              head     = snake.getHead();
    const std::vector<Coordinate>& body     = snake.getBody();
    const Direction&               dir      = snake.getDirection();
    const Coordinate&              applePos = apple.getCoordinate();

    grid[applePos.x][applePos.y] = '@';

    if (snake.getStatus() == SnakeStatus::Dead) {
        // Replace the entire snake with '*' to visualise the crash site.
        grid[head.x][head.y] = '*';
        for (const auto& [x, y] : body) grid[x][y] = '*';
        return;
    }

    // Draw the head as a direction arrow so the player can see where it's headed.
    constexpr char HEAD_CHAR[4] = {'^', '>', 'v', '<'};
    grid[head.x][head.y] = HEAD_CHAR[(int)dir];

    for (const auto& [x, y] : body) {
        if (x >= 0 && x < nRow && y >= 0 && y < nCol)
            grid[x][y] = '#';
    }
}

void Space::print() const {
    for(const auto &row : grid) {
        for(const auto &c : row) {
            if(c == '#' || c == 'v' || c == '^' || c == '>' || c == '<') {
                std::cout << GREEN << c << RESET;
            } else if(c == '@') {
                std::cout << RED << c << RESET;
            } else {
                std::cout << c;
            }
        }
        std::cout << "\n";
    }
}

bool Space::isSnakeAlive() const {
    return snake.getStatus() == SnakeStatus::Alive;
}

int Space::getScore() const {
    return snake.getLength() - INITIAL_SNAKE_LEN;
}

int Space::getSnakeLength() const {
    return snake.getLength();
}

int Space::getNRow() const {
    return nRow;
}

int Space::getNCol() const {
    return nCol;
}
