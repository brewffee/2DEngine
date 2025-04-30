#include "../../include/math/Vec3.h"

Vec3::Vec3() = default;
Vec3::Vec3(const float x, const float y, const float z): x(x), y(y), z(z) {}
Vec3::Vec3(const double x, const double y, const double z): x((float) x), y((float) y), z((float) z) {}
Vec3::Vec3(const int x, const int y, const int z): x((float) x), y((float) y), z((float) z) {}

// //////////////////////////////////////////////////////////////////////////////////////////

Vec3 Vec3::of(int xyz) { return { xyz, xyz, xyz }; }
Vec3 Vec3::of(float xyz) { return { xyz, xyz, xyz }; }
Vec3 Vec3::of(double xyz) { return { xyz, xyz, xyz }; }

Vec3 Vec3::zero() { return { 0, 0, 0 }; }

// //////////////////////////////////////////////////////////////////////////////////////////

Vec3 Vec3::operator+(const Vec3 &other) const { return { x + other.x, y + other.y, z + other.z }; }
Vec3 Vec3::operator-(const Vec3 &other) const { return { x - other.x, y - other.y, z - other.z }; }
Vec3 Vec3::operator*(const Vec3 &other) const { return { x * other.x, y * other.y, z * other.z }; }
Vec3 Vec3::operator/(const Vec3 &other) const { return { x / other.x, y / other.y, z / other.z }; }

Vec3 Vec3::operator+(const float other) const { return { x + other, y + other, z + other }; }
Vec3 Vec3::operator-(const float other) const { return { x - other, y - other, z - other }; }
Vec3 Vec3::operator*(const float other) const { return { x * other, y * other, z * other }; }
Vec3 Vec3::operator/(const float other) const { return { x / other, y / other, z / other }; }
