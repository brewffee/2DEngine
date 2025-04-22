#include "../../include/math/Transform.h"

Transform::Transform(Vec2 pos, Vec2 scale, Vec3 rotation, bool center_origin):
    position(pos),
    scale(scale),
    rotation(rotation),
    center_origin(center_origin) {}
    
Transform *Transform::zero() { return new Transform(); }

Transform *Transform::from_pos(Vec2 pos) { return new Transform(pos, {0,0}, {0,0,0}); }
Transform *Transform::from_pos(float x, float y) { return new Transform({x, y}); }
Transform *Transform::from_pos(float xy) { return new Transform({xy, xy}); }

Transform *Transform::from_scale(Vec2 scale) { return new Transform({0,0}, scale, {0,0,0}); }
Transform *Transform::from_scale(float x, float y) { return new Transform({0,0}, {x, y}, {0,0,0}); }
Transform *Transform::from_scale(float xy) { return new Transform({0,0}, {xy, xy}, {0,0,0}); }

Transform *Transform::from_rotation(Vec3 rotation) { return new Transform({0,0}, {0,0}, rotation); }
Transform *Transform::from_rotation(float x, float y, float z) { return new Transform({0,0}, {0,0}, {x, y, z}); }
Transform *Transform::from_rotation(float xyz) { return new Transform({0,0}, {0,0}, {xyz, xyz, xyz}); }
