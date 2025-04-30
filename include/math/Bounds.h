#pragma once

// Defines the outer bounds of an object
// todo: function for checking if a point is within bounds
// todo: function for checking if two bounds intersect
struct alignas(16) Bounds {
    float left, right, top, bottom;
};
