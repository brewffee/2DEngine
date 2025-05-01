#pragma once

#include "../macros.h"

/**
 * A struct representing data in 3D space.
 */
struct alignas(16) Vec3 {
    float x{}, y{}, z{};
    
    Vec3();
    Vec3(float x, float y, float z);
    Vec3(double x, double y, double z);
    Vec3(int x, int y, int z);
    
    /** Creates a Vec3 from a single number */
    attr(CONST) static Vec3 of(int xyz);
    attr(CONST) static Vec3 of(float xyz);
    attr(CONST) static Vec3 of(double xyz);

    /** Returns { 0, 0, 0 }. Equivalent to Vec3() */
    attr(CONST) static Vec3 zero();

    attr(PURE) Vec3 operator+(const Vec3 &other) const;
    attr(PURE) Vec3 operator-(const Vec3 &other) const;
    attr(PURE) Vec3 operator*(const Vec3 &other) const;
    attr(PURE) Vec3 operator/(const Vec3 &other) const;
    
    attr(PURE) Vec3 operator+(float other) const;
    attr(PURE) Vec3 operator-(float other) const;
    attr(PURE) Vec3 operator*(float other) const;
    attr(PURE) Vec3 operator/(float other) const;
};
