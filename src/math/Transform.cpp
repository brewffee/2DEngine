#include "../../include/math/Transform.h"

Transform::Transform(const Vec2 pos, const Vec2 scale, const Vec3 rotation, const bool center_origin):
    position(pos),
    scale(scale),
    rotation(rotation),
    center_origin(center_origin) {}

// //////////////////////////////////////////////////////////////////////////////////////////

Transform *Transform::from_pos(const Vec2 pos) { return new Transform(pos, {}, {}); }
Transform *Transform::from_pos(float x, float y) { return new Transform({ x, y }); }
Transform *Transform::from_pos(float xy) { return new Transform({ xy, xy }); }

Transform *Transform::from_scale(const Vec2 scale) { return new Transform({}, scale, {}); }
Transform *Transform::from_scale(float x, float y) { return new Transform({}, { x, y }, {}); }
Transform *Transform::from_scale(float xy) { return new Transform({}, { xy, xy }, {}); }

Transform *Transform::from_rotation(const Vec3 rotation) { return new Transform({}, {}, rotation); }
Transform *Transform::from_rotation(float x, float y, float z) { return new Transform({}, {}, { x, y, z }); }
Transform *Transform::from_rotation(float xyz) { return new Transform({}, {}, { xyz, xyz, xyz }); }

Transform *Transform::zero() { return new Transform; }
