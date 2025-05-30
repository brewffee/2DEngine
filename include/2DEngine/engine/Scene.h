#pragma once

#include <iostream>
#include <map>

#include "SceneItem.h"
#include "../macros.h"
#include "../color/RGBAColor.h"
#include "../util/Result.h"
#include "../util/Vector.h"

/**
 * The class representing the scene. Accepts a map of children and a bool should_quit.
 * todo: enqueue a scene to switch to or ask engine to handle the next scene when this one exits
 */
class Scene {
    public_props:
        std::map<int, Vector<SceneItem*>> children;
        RGBAColor background_color = { 0, 0, 0 };
        
        bool update_enabled = true;
        bool draw_enabled = true;
        bool input_enabled = true;
        bool should_quit = false;

    public_methods:
        Scene(); virtual ~Scene();

        GETTER_SETTER(RGBAColor, background_color);
        GETTER_SETTER(bool, update_enabled);
        GETTER_SETTER(bool, draw_enabled);
        GETTER_SETTER(bool, input_enabled);
        GETTER_SETTER(bool, should_quit);

        template<typename T = SceneItem>
        Result<T*> get_child(const char* key);
        void add_child(SceneItem *child, int layer = 0);
        void remove_child(const std::string &name);

        virtual void update_children();
        virtual void update(double delta) no_default;
    
        virtual void draw_children();
        
        virtual void draw() no_default;
        virtual void input() no_default;
};
