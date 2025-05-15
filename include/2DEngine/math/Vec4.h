#pragma once

#include "../macros.h"

struct Vec4 {
    float x{}, y{}, z{}, w{};

    Vec4();
    Vec4(float x, float y, float z, float w);
    Vec4(double x, double y, double z, double w);
    Vec4(int x, int y, int z, int w);

    /** Creates a Vec4 from a single number */
    attr(CONST) static Vec4 of(int xyzw);
    attr(CONST) static Vec4 of(float xyzw);
    attr(CONST) static Vec4 of(double xyzw);

    /** Returns { 0, 0, 0, 0 }. Equivalent to Vec4() */
    attr(CONST) static Vec4 zero();

    attr(PURE) Vec4 operator+(const Vec4 &other) const;
    attr(PURE) Vec4 operator-(const Vec4 &other) const;
    attr(PURE) Vec4 operator*(const Vec4 &other) const;
    attr(PURE) Vec4 operator/(const Vec4 &other) const;

    attr(PURE) Vec4 operator+(float other) const;
    attr(PURE) Vec4 operator-(float other) const;
    attr(PURE) Vec4 operator*(float other) const;
    attr(PURE) Vec4 operator/(float other) const;
};
