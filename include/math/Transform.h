#include "Vec2.h"
#include "Vec3.h"

/**
 * A struct representing a transformation of an object in 2D space.
 * Accepts construction from a Point, a float size, a Rotation, and a bool center_origin
 */
struct Transform {
    Vec2 position;
    Vec2 scale;
    Vec3 rotation;
    [[maybe_unused]] bool center_origin{};
    // Alignment alignment{};
    
    explicit Transform(Vec2 pos = {}, Vec2 scale = {}, Vec3 rotation = {}, bool center_origin = true);
        
    // allows instantiating without having to provide all of the args
    static Transform *zero();
    
    static Transform *from_pos(Vec2 pos);
    static Transform *from_pos(float x, float y);
    static Transform *from_pos(float xy);
    
    static Transform *from_scale(Vec2 scale);
    static Transform *from_scale(float x, float y);
    static Transform *from_scale(float xy);
    
    static Transform *from_rotation(Vec3 rotation);
    static Transform *from_rotation(float x, float y, float z);
    static Transform *from_rotation(float xyz);
};
