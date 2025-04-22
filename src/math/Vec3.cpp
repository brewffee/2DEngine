#include "../../include/math/Vec3.h"

Vec3::Vec3(): x(0.f), y(0.f), z(0.f) {}
Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z) {}
Vec3::Vec3(double x, double y, double z): x((float) x), y((float) y), z((float) z) {}
Vec3::Vec3(int x, int y, int z): x((float) x), y((float) y), z((float) z) {}

Vec3::Vec3(float xyz): x(xyz), y(xyz) {}
Vec3::Vec3(double xyz): x((float) xyz), y((float) xyz) {}
Vec3::Vec3(int xyz): x((float) xyz), y((float) xyz) {}

// math operators
Vec3 Vec3::operator+(const Vec3 &other) const { return { x + other.x, y + other.y, z + other.z }; }
Vec3 Vec3::operator-(const Vec3 &other) const { return { x - other.x, y - other.y, z - other.z }; }
Vec3 Vec3::operator*(const Vec3 &other) const { return { x * other.x, y * other.y, z * other.z }; }
Vec3 Vec3::operator/(const Vec3 &other) const { return { x / other.x, y / other.y, z / other.z }; }

Vec3 Vec3::operator+(float other) const { return { x + other, y + other, z + other }; }
Vec3 Vec3::operator-(float other) const { return { x - other, y - other, z - other }; }
Vec3 Vec3::operator*(float other) const { return { x * other, y * other, z * other }; }
Vec3 Vec3::operator/(float other) const { return { x / other, y / other, z / other }; }
