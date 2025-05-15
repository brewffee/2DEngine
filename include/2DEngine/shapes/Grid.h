#pragma once

#include "../color/RGBAColor.h"
#include "../engine/Engine.h"
#include "../shapes/Shape.h"

class Grid: public Shape {
    RGBAColor color;
    float interval;
    float line_width = 1.f;
    long max_vertices = 4096; // there's got to be a beatter way for this

    ShaderProgram shader = {
        "../src/shaders/basic/vertex.glsl",
        "../src/shaders/basic/fragment.glsl"
    };

    public:
        ~Grid() override = default;
        explicit Grid(Transform *transform, const RGBAColor &color, float interval);

        GETTER_SETTER(RGBAColor, color);
        GETTER_SETTER(float, interval);
        GETTER_SETTER(float, line_width);
        GETTER_SETTER(int, max_vertices);

        void gl_draw() override;
};
