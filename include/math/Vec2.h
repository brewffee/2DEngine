#pragma once

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
    
    explicit Vec2(float xy);
    explicit Vec2(double xy);
    explicit Vec2(int xy);
    
    // math operators
    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator*(const Vec2 &other) const;
    Vec2 operator/(const Vec2 &other) const;
    
    Vec2 operator+(float other) const;
    Vec2 operator-(float other) const;
    Vec2 operator*(float other) const;
    Vec2 operator/(float other) const;
    
    static Vec2 to_world(Vec2 src, float w, float h, float ex, float ey);
};
