#pragma once

/**
 * A struct representing data in 3D space
 */
struct Vec3 {
    float x = 0, y = 0, z = 0;
    
    Vec3();
    Vec3(float x, float y, float z);
    Vec3(double x, double y, double z);
    Vec3(int x, int y, int z);
    
    explicit Vec3(float xyz);
    explicit Vec3(double xyz);
    explicit Vec3(int xyz);
    
    // math operators
    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(const Vec3 &other) const;
    Vec3 operator/(const Vec3 &other) const;
    
    Vec3 operator+(float other) const;
    Vec3 operator-(float other) const;
    Vec3 operator*(float other) const;
    Vec3 operator/(float other) const;
};
