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
        int draw_mode{}; // todo: custom type
    
    public_methods:
        Shape() = default; ~Shape() override = default;
        explicit Shape(Transform *transform, RGBAColor color);
};

// todo: more shapes + textured quad
