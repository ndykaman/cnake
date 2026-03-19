#pragma once

#include "../direction/direction.h"

// Row delta per direction: North=-1, East=0, South=+1, West=0.
constexpr int MOVE_DX[4] = {-1, 0, 1, 0};

// Column delta per direction: North=0, East=+1, South=0, West=-1.
constexpr int MOVE_DY[4] = {0, 1, 0, -1};

// Opposite of MOVE_DX: used to place body segments behind the head on spawn.
constexpr int BODY_DX[4] = {1, 0, -1, 0};

// Opposite of MOVE_DY: used to place body segments behind the head on spawn.
constexpr int BODY_DY[4] = {0, -1, 0, 1};

// Wraps `value` into [0, mod) with correct handling of negative numbers.
inline int wrap(int value, int mod) {
    value %= mod;
    if (value < 0) value += mod;
    return value;
}

// Returns true if `a` and `b` are opposite directions.
inline bool isOppositeDirection(Direction a, Direction b) {
    return __builtin_abs((int)a - (int)b) == 2;
}
