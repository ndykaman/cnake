#pragma once

// Cardinal directions used for snake movement.
// The integer values are ordered so that opposite directions differ by exactly 2,
// which makes reverse-direction checks simple: abs(a - b) == 2.
enum class Direction {
    North = 0,
    East  = 1,
    South = 2,
    West  = 3
};
