#pragma once

#include "../color/RGBAColor.h"
#include "../engine/SceneItem.h"

/**
 * The generic class for all basic 2D shapes. Accepts a Transform and an RGBAColor on construction.
 * todo: transparency flag
 */
class Shape: public SceneItem {
    public_props:
        RGBAColor color = RGBAColors::white;
        unsigned int vao = 0;
        unsigned int  vbo = 0;
    
    public_methods:
        Shape() = default; ~Shape() override = default;
        explicit Shape(Transform *transform, const RGBAColor &color);
};

// todo: more shapes + textured quad
