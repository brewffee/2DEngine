#pragma once

#include "../util/Vector.h"

struct Input {
    enum PressState { RELEASED, PRESSED, HELD }; // Enum for press state
    
    const char* name;
    Vector<int> keycodes;
    PressState pressState = RELEASED;
};
