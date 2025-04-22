#pragma once

#include <vector>

struct Input {
    enum PressState { RELEASED, PRESSED, HELD }; // Enum for press state
    
    const char* name;
    std::vector<int> keycodes;
    PressState pressState = RELEASED;
};
