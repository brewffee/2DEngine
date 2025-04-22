#pragma once

#include <iostream>
#include <unordered_map>

#include "../macros.h"
#include "SceneItem.h"

/**
 * The class representing the scene. Accepts a map of children and a bool should_quit.
 * todo: enqueue a scene to switch to or ask engine to handle the next scene when this one exits
 */
class Scene {
    public_props:
        std::unordered_map<std::string, SceneItem*> children; // todo: replace this type
        bool should_quit = false;
        
        bool update_enabled = true;
        bool draw_enabled = true;
        bool input_enabled = true;
    
    public_methods:
        Scene() = default; virtual ~Scene();
        
        template<typename T = SceneItem>
        Result<T*> get_child(const char* key);
        void add_child(const std::string &name, SceneItem *child, int layer = 0);
        void remove_child(const std::string &name);
        
        virtual void update(double delta) no_default;
    
        // todo: layers
        virtual void draw_children(); // might not wanna override this? idk
        
        virtual void draw() no_default;
        virtual void input() no_default;
};
