#pragma once

#include "Vec2.h"
#include "Vec3.h"

/**
 * A struct representing a transformation of an object in 2D space.
 * Accepts construction from a Point, a float size, a Rotation, and a bool center_origin
 */
struct alignas(64) Transform {
    Vec2 position;
    Vec2 scale;
    Vec3 rotation;
    bool center_origin{};
    // todo: Alignment alignment{}; ??

    explicit Transform(Vec2 pos = {}, Vec2 scale = {}, Vec3 rotation = {}, bool center_origin = true);

    /** Creates a Transform when only given a position. Equivalent to new Transform(position); */
    static Transform *from_pos(Vec2 pos);
    static Transform *from_pos(float x, float y);
    static Transform *from_pos(float xy);

    /** Creates a Transform when only given a scale. Equivalent to new Transform({}, scale); */
    static Transform *from_scale(Vec2 scale);
    static Transform *from_scale(float x, float y);
    static Transform *from_scale(float xy);

    /** Creates a Transform when only given a rotation. Equivalent to new Transform({}, {}, rotation); */
    static Transform *from_rotation(Vec3 rotation);
    static Transform *from_rotation(float x, float y, float z);
    static Transform *from_rotation(float xyz);

    /** Returns an empty Transform. Equivalent to new Transform() */
    static Transform *zero();
};
