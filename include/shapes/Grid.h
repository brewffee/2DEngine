#pragma once

#include "../color/RGBAColor.h"
#include "../engine/Engine.h"
#include "../engine/SceneItem.h"

class Grid: public SceneItem {
    public_props:
        RGBAColor color = RGBAColors::white;
        float interval = 1.f;
    
    public_methods:
        Grid() = default; ~Grid() override = default;
        explicit Grid(Transform *transform, const RGBAColor &color, float interval);
    
        void gl_draw() override;
};
