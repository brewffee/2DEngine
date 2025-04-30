#pragma once

#include "../macros.h"

/**
 * A struct representing data in 2D space.
 */
struct Vec2 {
    float x{};
    float y{};
    
    Vec2();
    Vec2(float x, float y);
    Vec2(double x, double y);
    Vec2(int x, int y);

    /** Creates a Vec2 from a single number */
    attr(const) static Vec2 of(int xy);
    attr(const) static Vec2 of(float xy);
    attr(const) static Vec2 of(double xy);

    /** Returns { 0, 0 }. Equivalent to Vec2() */
    attr(const) static Vec2 zero();

    attr(pure) Vec2 operator+(const Vec2 &other) const;
    attr(pure) Vec2 operator-(const Vec2 &other) const;
    attr(pure) Vec2 operator*(const Vec2 &other) const;
    attr(pure) Vec2 operator/(const Vec2 &other) const;

    attr(pure) Vec2 operator+(float other) const;
    attr(pure) Vec2 operator-(float other) const;
    attr(pure) Vec2 operator*(float other) const;
    attr(pure) Vec2 operator/(float other) const;

    /**
     * Converts a window point to a world point. This function may change in the future.
     * @param src The window point
     * @param w The width of the window
     * @param h The height of the window
     * @param ex The visible extent of X in world plane (before going offscreen)
     * @param ey The visible extent of Y in world plane (before going offscreen)
     */
    attr(const) static Vec2 to_world(Vec2 src, float w, float h, float ex, float ey);
} attr(aligned(8));
