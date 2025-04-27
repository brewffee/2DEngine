#include "../../include/math/Vec2.h"

Vec2::Vec2(): x(0.f), y(0.f) {}
Vec2::Vec2(float x, float y): x(x), y(y) {}
Vec2::Vec2(double x, double y): x((float) x), y((float) y) {}
Vec2::Vec2(int x, int y): x((float) x), y((float) y) {}

Vec2::Vec2(float xy): x(xy), y(xy) {}
Vec2::Vec2(double xy): x((float) xy), y((float) xy) {}
Vec2::Vec2(int xy): x((float) xy), y((float) xy) {}

// math operators
Vec2 Vec2::operator+(const Vec2 &other) const { return { x + other.x, y + other.y }; }
Vec2 Vec2::operator-(const Vec2 &other) const { return { x - other.x, y - other.y }; }
Vec2 Vec2::operator*(const Vec2 &other) const { return { x * other.x, y * other.y }; }
Vec2 Vec2::operator/(const Vec2 &other) const { return { x / other.x, y / other.y }; }

Vec2 Vec2::operator+(float other) const { return { x + other, y + other }; }
Vec2 Vec2::operator-(float other) const { return { x - other, y - other }; }
Vec2 Vec2::operator*(float other) const { return { x * other, y * other }; }
Vec2 Vec2::operator/(float other) const { return { x / other, y / other }; }

Vec2 Vec2::to_world(Vec2 src, float w, float h, float ex, float ey) {
    // src.x = Window point x position
    // src.y = Window point y position
    // w = Window width
    // h = Window height
    // ex = Visible extent of X in world plane (before going offscreen)
    // ey = Visible extent of Y in world plane (before going offscreen)
    return { ((src.x/w) * 2 - 1) * ex, -(((src.y/h) * 2) - 1) * ey };
}
