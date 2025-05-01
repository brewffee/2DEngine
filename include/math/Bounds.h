#pragma once

#include "../macros.h"

class Vec2;

/**
 * A struct representing the outer bounds of an object
 */
struct alignas(16) Bounds {
    float left{}, right{}, top{}, bottom{};

    Bounds();
    Bounds(float l, float r, float t, float b);
    Bounds(double l, double r, double t, double b);
    Bounds(int l, int r, int t, int b);

    /** Creates Bounds from a point and a size */
    attr(CONST) static Bounds from(const Vec2 &point, const Vec2 &size, bool centered = true);

    /** Returns { 0, 0, 0, 0 }. Equivalent to Bounds() */
    attr(CONST) static Bounds zero();

    attr(PURE) Bounds operator+(const Bounds &other) const;
    attr(PURE) Bounds operator-(const Bounds &other) const;
    attr(PURE) Bounds operator*(const Bounds &other) const;
    attr(PURE) Bounds operator/(const Bounds &other) const;

    attr(PURE) Bounds operator+(float other) const;
    attr(PURE) Bounds operator-(float other) const;
    attr(PURE) Bounds operator*(float other) const;
    attr(PURE) Bounds operator/(float other) const;

    /**
     * Checks if a point is within this bounding area
     * @param point The point to check
     */
    attr(nodiscard) bool contains(const Vec2 &point) const;

    /**
     * Checks if another bounding area interesects with this one
     * @param other The other bounding area to check
     */
    attr(nodiscard) bool intersects(const Bounds &other) const;
};
