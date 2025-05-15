#include "2DEngine/math/Vec2.h"

Vec2::Vec2() = default;
Vec2::Vec2(const float x, const float y): x(x), y(y) {}
Vec2::Vec2(const double x, const double y): x((float) x), y((float) y) {}
Vec2::Vec2(const int x, const int y): x((float) x), y((float) y) {}

// //////////////////////////////////////////////////////////////////////////////////////////

Vec2 Vec2::of(int xy) { return { xy, xy }; }
Vec2 Vec2::of(float xy) { return { xy, xy }; }
Vec2 Vec2::of(double xy) { return { xy, xy }; }

Vec2 Vec2::zero() { return {}; }

// //////////////////////////////////////////////////////////////////////////////////////////

Vec2 Vec2::operator+(const Vec2 &other) const { return { x + other.x, y + other.y }; }
Vec2 Vec2::operator-(const Vec2 &other) const { return { x - other.x, y - other.y }; }
Vec2 Vec2::operator*(const Vec2 &other) const { return { x * other.x, y * other.y }; }
Vec2 Vec2::operator/(const Vec2 &other) const { return { x / other.x, y / other.y }; }

Vec2 Vec2::operator+(const float other) const { return { x + other, y + other }; }
Vec2 Vec2::operator-(const float other) const { return { x - other, y - other }; }
Vec2 Vec2::operator*(const float other) const { return { x * other, y * other }; }
Vec2 Vec2::operator/(const float other) const { return { x / other, y / other }; }

// //////////////////////////////////////////////////////////////////////////////////////////

Vec2 Vec2::to_world(const Vec2 src, const float w, const float h, const float ex, const float ey) {
    // src.x = Window point x position
    // src.y = Window point y position
    // w = Window width
    // h = Window height
    // ex = Visible extent of X in world plane (before going offscreen)
    // ey = Visible extent of Y in world plane (before going offscreen)
    return { ((src.x/w) * 2 - 1) * ex, -(((src.y/h) * 2) - 1) * ey };
}
