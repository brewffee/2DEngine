#pragma once

#include <cmath>
#include <GLFW/glfw3.h>

#include "../color/RGBAColor.h"
#include "../engine/Engine.h"
#include "../engine/SceneItem.h"

class Grid: public SceneItem {
    public_props:
        RGBAColor color = RGBAColors::white;
        float interval = 1.f;
    
    public_methods:
        Grid() = default; ~Grid() override = default;
        explicit Grid(Transform *transform, RGBAColor color, float interval);
    
        void gl_draw() override;
};
