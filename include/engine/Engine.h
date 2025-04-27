#pragma once

#include <cmath>
#include <cstdint>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include "../macros.h"
#include "../math/Vec2.h"
#include "../math/Bounds.h"
#include "Input.h"
#include "Scene.h"

/**
 * The main singleton for the engine
 */
class Engine {
    CREATE_SINGLETON_CLASS(Engine)
    
    private_props:
        double updates_per_frame = 1.0 / 75.0;
        int32_t target_framerate = 0; // todo: actually implement
        bool vsync = false;
        
        int32_t window_width = 800; // todo: require user to set default window size
        int32_t window_height = 600;
        float aspect_ratio = (float) window_width / (float) window_height;
        
        const char* title = "Application";
        
        double current_time{}, elapsed_time{}, prev_time{}, accumulator{};
        int frame_count = 0;
    
        Bounds window_bounds{};
        static Bounds world_bounds; // window_bounds, but adjusted for camera movement
        static Vec2 mouse_pos; // todo: mouse class
        
        GLFWwindow *glfw{};
        int status = 0; // todo: i swear i will use you soon
        double fps{};
        std::unordered_map<const char*, Input> input_map;
        std::unordered_map<const char*, Input> scene_list; // todo apparently this is unused, fix that lmao
        Scene *default_scene{};
        Scene *current_scene{};
        bool window_focused = false;
    
    private_methods:
        /**
         * Private method for calculating the current framerate.
         * Returns -1 until calculation is finished
         */
        static double _get_current_framerate(int &frames, double &ptime);
        
        /**
         * GLFW callback for when the window is resized.
         * todo: allow user to provide custom callbacks and call here
         */
        static void _glfw_framebuffer_size_callback(GLFWwindow*, int width, int height);
        static void _glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
        static void _glfw_mouse_button_callback(GLFWwindow*, int button, int action, int mods);
        static void _glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
        
        void _do_key_event_gl(int key, int _scancode, int action, int _mods);
        // todo: scale modes
        // todo: a function similar to this needs to run on instantiation
        void _do_reshape_viewport_gl(int width, int height);
    
    public_methods:
        ~Engine();
        
        // (T, var) Defines and implements basic T get_var() and void set_var(T var_) methods
        GETTER_SETTER(double, updates_per_frame);
        GETTER_SETTER(int, target_framerate);
        GETTER_SETTER(bool, vsync);
        GETTER_SETTER(int32_t, window_width);
        GETTER_SETTER(int32_t, window_height);
        GETTER_SETTER(const char*, title);
        
        GETTER_REF(Bounds, window_bounds);
        GETTER_REF(Bounds, world_bounds);
        GETTER(Vec2, mouse_pos);
        
        GETTER(Scene*, current_scene); // setting would be handled by queue system
        GETTER_SETTER(Scene*, default_scene); //todo: add to scene list
        GETTER(double, fps);
        GETTER(bool, window_focused);
        GETTER(GLFWwindow*, glfw);
        GETTER(int, status);
        
        // todo:rework
        /**
         * Recalculates the world bounds according to the camera's position and the window's size
         * @param origin_x
         * @param origin_y
         */
        void update_world_bounds(float origin_x = 0.f, float origin_y = 0.f) const;
        
        /**
         * Adds a new input structure to the input map
         * @param input
         */
        void add_input(const Input &input);
        
        /**
         * Checks if the input is pressed
         * @param name
         */
        bool is_input_pressed(const char* name) const;
        
        /**
         * Checks if the input is held
         * @param name
         */
        bool is_input_held(const char* name) const;
        
        [[nodiscard]] Vec2 get_mouse_window_position() const;
        [[nodiscard]] Vec2 get_window_size() const;
        
        // todo: allow user to resize the window
    
        void start();
};
