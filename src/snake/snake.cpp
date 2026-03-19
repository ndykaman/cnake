#include "snake.h"
#include "../utils/utils.h"
#include <random>

static constexpr int INITIAL_SNAKE_LEN = 5;

Snake::Snake() : head({0, 0}), direction(Direction::East),
                 length(1), status(SnakeStatus::Alive) {}

Snake::Snake(int nRow, int nCol) : length(INITIAL_SNAKE_LEN), status(SnakeStatus::Alive) {
    // Keep the initial body fully inside the grid by shrinking the spawn zone.
    const int margin = INITIAL_SNAKE_LEN - 3;
    std::uniform_int_distribution<> distX(margin, nRow - 1 - margin);
    std::uniform_int_distribution<> distY(margin, nCol - 1 - margin);
    std::uniform_int_distribution<> distD(0, 3);

    std::mt19937 gen{std::random_device{}()};

    head      = {distX(gen), distY(gen)};
    direction = static_cast<Direction>(distD(gen));

    // Build body segments extending away from the head so they don't overlap it.
    body.reserve(length - 1);
    for (int i = 1; i < length; ++i) {
        body.push_back({
            wrap(head.x + i * BODY_DX[(int)direction], nRow),
            wrap(head.y + i * BODY_DY[(int)direction], nCol)
        });
    }
}

void Snake::move(int nRow, int nCol, Direction newDirection) {
    if (isOppositeDirection(direction, newDirection)) return;

    // Shift every body segment one step toward the head before advancing the head.
    for (int i = (int)body.size() - 1; i > 0; --i)
        body[i] = body[i - 1];
    body[0] = head;

    head = {
        wrap(head.x + MOVE_DX[(int)newDirection], nRow),
        wrap(head.y + MOVE_DY[(int)newDirection], nCol)
    };
    direction = newDirection;
}

void Snake::grow(const Apple& apple) {
    // Extrapolate one segment past the current tail in the same direction as the tail.
    const Coordinate& tail       = body.back();
    const Coordinate& beforeTail = body[body.size() - 2];

    Coordinate newTail = {
        tail.x + (tail.x - beforeTail.x),
        tail.y + (tail.y - beforeTail.y)
    };

    for (int i = 0; i < apple.getValue(); ++i)
        body.push_back(newTail);

    length += apple.getValue();
}

void Snake::kill() { status = SnakeStatus::Dead; }

int                          Snake::getLength()    const { return length; }
Coordinate                   Snake::getHead()      const { return head; }
Direction                    Snake::getDirection() const { return direction; }
const std::vector<Coordinate>& Snake::getBody()   const { return body; }
SnakeStatus                  Snake::getStatus()    const { return status; }
