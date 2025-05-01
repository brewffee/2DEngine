#include "../../include/math/Bounds.h"
#include "../../include/math/Vec2.h"

Bounds::Bounds() = default;

Bounds::Bounds(const float l, const float r, const float t, const float b):
    left(l), right(r), top(t), bottom(b) {}

Bounds::Bounds(const double l, const double r, const double t, const double b):
    left((float) l), right((float) r), top((float) t), bottom((float) b) {}

Bounds::Bounds(const int l, const int r, const int t, const int b):
    left((float) l), right((float) r), top((float) t), bottom((float) b) {}

// //////////////////////////////////////////////////////////////////////////////////////////

Bounds Bounds::from(const Vec2 &point, const Vec2 &size, const bool centered) {
    if (centered) {
        return {
            point.x - (size.x / 2),     // left
            point.x + (size.x / 2),     // right
            point.y + (size.y / 2),     // top
            point.y - (size.y / 2)      // bottom

        };
    }

    return {
        point.x,                    // left
        point.x + size.x,           // right
        point.y + size.y,           // top
        point.y                     // bottom
    };
}

Bounds Bounds::zero() { return { 0, 0, 0, 0 }; }

// //////////////////////////////////////////////////////////////////////////////////////////

Bounds Bounds::operator+(const Bounds &other) const {
    return { left + other.left, right + other.right, top + other.top, bottom + other.bottom };
}

Bounds Bounds::operator-(const Bounds &other) const {
    return { left - other.left, right - other.right, top - other.top, bottom - other.bottom };
}

Bounds Bounds::operator*(const Bounds &other) const {
    return { left * other.left, right * other.right, top * other.top, bottom * other.bottom };
}

Bounds Bounds::operator/(const Bounds &other) const {
    return { left / other.left, right / other.right, top / other.top, bottom / other.bottom };
}

Bounds Bounds::operator+(const float other) const {
    return { left + other, right + other, top + other, bottom + other };
}

Bounds Bounds::operator-(const float other) const {
    return { left - other, right - other, top - other, bottom - other };
}

Bounds Bounds::operator*(const float other) const {
    return { left * other, right * other, top * other, bottom * other };
}

Bounds Bounds::operator/(const float other) const {
    return { left / other, right / other, top / other, bottom / other };
}

// //////////////////////////////////////////////////////////////////////////////////////////

bool Bounds::contains(const Vec2 &point) const {
    return point.x >= left && point.x <= right && point.y >= bottom && point.y <= top;
}

bool Bounds::intersects(const Bounds &other) const {
    return left <= other.right && right >= other.left && top >= other.bottom && bottom <= other.top;
}
