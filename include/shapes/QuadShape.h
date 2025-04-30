#pragma once

#include <GLFW/glfw3.h>

#include "Shape.h"

/**
 * A class representing a square in 2D space. Accepts a Transform and an RGBAColor on construction.
 */
class QuadShape: public Shape {
    public_props:
        int draw_mode = GL_QUADS;
    
    public_methods:
        QuadShape() = default; ~QuadShape() override = default;
        explicit QuadShape(Transform *transform, const RGBAColor &color);
    
        void gl_draw() override;
};
