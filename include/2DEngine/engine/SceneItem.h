#pragma once

#include "../macros.h"
#include "../math/Transform.h"

class Scene;

/**
 * The generic class for all child objects of a scene. Only accepts construction from a Transform,
 * and cannot be drawn unless overridden.
 *
 * To make sure you can access a child after exiting its scope, give it a name bedore adding it to
 * a scene.
 */
class SceneItem {
    public_props:
        Transform *transform{};

        const char *name = "unknown";
        
        // root items will return nullptr for parent, watch out!!!
        Scene *scene{};
        SceneItem *parent{};
        
    public_methods:
        SceneItem() = default;
        explicit SceneItem(Transform *transform);
        virtual ~SceneItem();
        
        virtual void gl_draw() no_default;
};
