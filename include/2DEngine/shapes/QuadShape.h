#pragma once

#include "Shape.h"
#include "2DEngine/shaders/ShaderProgram.h"

/**
 * A class representing a square in 2D space. Accepts a Transform and an RGBAColor on construction.
 */
class QuadShape: public Shape {
    ShaderProgram shader = {
        "../src/shaders/basic/vertex.glsl",
        "../src/shaders/basic/fragment.glsl"
    };

    public:
       ~QuadShape() override = default;
        explicit QuadShape(Transform *transform = {}, const RGBAColor &color = RGBAColors::white);
    
        void gl_draw() override;
};
