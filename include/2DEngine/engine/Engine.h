#pragma once

#include <unordered_map>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Scene.h"
#include "../macros.h"
#include "../math/Bounds.h"
#include "../math/Vec2.h"
#include "2DEngine/shaders/ShaderProgram.h"

/**
 * Enum class for different content scaling modes
 * - SCALE: scale content size to fit
 * - STRETCH: stretch contents when a dimension is too small
 * - KEEP: contents stay the same size independent of window
 *
 * todo: add aspect-preserving modes
 * todo: are these the right terms? i'm not well versed
 */
enum class ScaleMode: uint8_t {
    SCALE, // scale content size to fit
    STRETCH, // stretch contents when a dimension is too small
    KEEP // contents stay the same size independent of window
};

/**
 * The main singleton for the engine
 */
class Engine {
    CREATE_SINGLETON_CLASS(Engine)
    
    private_props:
        double updates_per_frame = 1.0 / 75.0;
        int32_t target_framerate = 0; // todo: actually implement
        bool vsync = false;

        Vec2 window_size = { 400, 400 };
        float aspect_ratio = window_size.x / window_size.y;
        ScaleMode scale_mode = ScaleMode::STRETCH;
        glm::mat4 projection_matrix{};
        ShaderProgram vp_shader = {
            "../src/shaders/basic/vertex.glsl",
            "../src/shaders/basic/fragment.glsl"
        };

        const char* title = "Application"; // use custom string type

        double current_time{}, elapsed_time{}, prev_time{}, accumulator{};
        int frame_count = 0;

        Bounds window_bounds;
        Bounds world_bounds; // window_bounds, but adjusted for camera movement
        Vec2 mouse_pos; // todo: mouse class

        GLFWwindow *glfw{};

        int status = 0; // todo: i swear i will use you soon
        double fps{};
        std::unordered_map<const char*, Input> input_map{};
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

        // todo: a function similar to this needs to run on instantiation
        void _do_reshape_viewport_gl(int width, int height);

    public_methods:
        ~Engine();
        // (T, var) Defines and implements basic T get_var() and void set_var(T var_) methods
        GETTER_SETTER(double, updates_per_frame);
        GETTER_SETTER(int, target_framerate);
        GETTER_SETTER(bool, vsync);
        GETTER(Vec2, window_size);
        GETTER_SETTER(ScaleMode, scale_mode);
        GETTER_REF(glm::mat4, projection_matrix);
        GETTER_SETTER(const char*, title);
        
        GETTER_REF(Bounds, window_bounds);
        GETTER_REF(Bounds, world_bounds);
        GETTER(Vec2, mouse_pos);
        
        GETTER(Scene*, current_scene); // setting would be handled by queue system
        GETTER_SETTER(Scene*, default_scene);
        GETTER(double, fps);
        GETTER(bool, window_focused);
        GETTER(GLFWwindow*, glfw);
        GETTER(int, status);
        
        /**
         * Recalculates the world bounds according to the camera's position and the window's size
         * @param origin_x
         * @param origin_y
         */
        void update_world_bounds(float origin_x = 0.f, float origin_y = 0.f);
        
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

        /**
         * Gets the mouse's position in window coordinates
         */
        [[nodiscard]] Vec2 get_mouse_window_position() const;

        // todo: allow setting initial window size

        /**
         * Sets the window's size
         * @param new_size - Vec2 of new width and height
         */
        void set_window_size(const Vec2 &new_size) const;

        /**
         *  Sets the window's size
         *  @param x - New width of the window
         *  @param y - New height of the window
         */
        void set_window_size(float x, float y) const;

        void init();
        void start();
};
