#pragma once

#include <cstdint>

#include "../util/Vector.h"

struct alignas(64) Input {
    enum PressState: uint8_t { RELEASED, PRESSED, HELD }; // Enum for press state
    
    const char* name;
    Vector<int> keycodes;
    PressState pressState = RELEASED;
};
