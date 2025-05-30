#include <cmath>

#include "2DEngine/engine/Engine.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>

#include "2DEngine/shaders/ShaderProgram.h"

double Engine::_get_current_framerate(int &frames, double &ptime) {
    const double delta = instance() -> current_time - ptime;
    
    ++frames;
    if (delta >= 1.0) {
        const double cfps = frames / delta;
        frames = 0;
        ptime = instance() -> current_time;
        return cfps;
    }
    
    return -1.0; // Please stand by !!
}

void Engine::_glfw_framebuffer_size_callback(GLFWwindow*, const int width, const int height) {
    instance()->_do_reshape_viewport_gl(width, height);
}

void Engine::_glfw_key_callback(GLFWwindow*, const int key, const int scancode, const int action, const int mods) {
    instance()->_do_key_event_gl(key, scancode, action, mods);
    if (instance() -> current_scene && instance() -> current_scene -> input_enabled)
        instance() -> current_scene -> input();
}

void Engine::_glfw_mouse_button_callback(GLFWwindow*, int button, int action, int mods) {
    // Engine doesn't have any special behavior here
    // todo: InputEvent class, and add KeyPressEvent, KeyReleaseEvent, KeyHoldEvent,
    //  MouseButtonPressEvent, MouseButtonReleaseEvent, MouseButtonHoldEvent,
    //  and probably Gamepad stuff in the future
    if (instance() -> current_scene && instance() -> current_scene -> input_enabled)
        instance() -> current_scene -> input();
}

void Engine::_glfw_cursor_pos_callback(GLFWwindow*, double xpos, double ypos) {
    // Get the current mouse position
    auto [width, height] = instance() -> get_window_size();
    auto &[left, right, top, bottom] = instance() -> get_window_bounds();
    
    // Convert to world coordinates
    instance() -> mouse_pos = Vec2::to_world({xpos, ypos}, width, height, right, top);
    if (instance() -> current_scene && instance() -> current_scene -> input_enabled)
        instance() -> current_scene -> input();
}

void Engine::_do_key_event_gl(const int key, int _scancode, const int action, int _mods) {
    for (auto &[name, input]: input_map) {
        // if any keycode is pressed, the entire input should be marked as pressed
        if (input.keycodes.contains(key)) {
            switch (action) {
                case GLFW_PRESS:
                    input.pressState = Input::PRESSED;
                    break;
                case GLFW_REPEAT:
                    input.pressState = Input::HELD;
                    break;
                default:
                    input.pressState = Input::RELEASED;
            }
        }
    }
}

void Engine::_do_reshape_viewport_gl(const int width, const int height) {
    aspect_ratio = (float) width / (float) height;
    auto &[left, right, top, bottom] = window_bounds;

    switch (scale_mode) {
        case ScaleMode::SCALE:
            // Sets new bounds based on the aspect ratio, using Y as the base
            left = -aspect_ratio;
            right = aspect_ratio;
            bottom = -1.f;
            top = 1.f;
            break;

        case ScaleMode::KEEP: {
            // Sets new bounds comparative to the default size
            // todo: set resolution to base these numbers on
            const Vec2 original_size = Vec2::of(400);
            const float width_ratio = (float) width / original_size.x;
            const float height_ratio = (float) height / original_size.y;

            left = -width_ratio;
            right = width_ratio;
            bottom = -height_ratio;
            top = height_ratio;
            break;
        }

        case ScaleMode::STRETCH: default:
            // Distorts the contents to fill the window space
            left = -1.f;
            right = 1.f;
            bottom = -1.f;
            top = 1.f;
            break;
    }

    window_size = { width, height };

    glViewport(0, 0, width, height);
    projection_matrix = glm::ortho(left, right, bottom, top);
    vp_shader.set_uniform("projection_matrix", projection_matrix);
}

// /////////////////////////////////////////////////////////////////////////////////////////

Engine::~Engine() {
    delete instance_;
    if (default_scene != current_scene) {
        delete default_scene;
    }
    delete current_scene;
}

void Engine::update_world_bounds(const float origin_x, const float origin_y) {
    world_bounds.left = window_bounds.left - origin_x;
    world_bounds.right = window_bounds.right - origin_x;
    world_bounds.top = window_bounds.top - origin_y;
    world_bounds.bottom = window_bounds.bottom - origin_y;
}

void Engine::add_input(const Input &input) {
    input_map.insert({ input.name, input });
}

bool Engine::is_input_pressed(const char* name) const {
    return input_map.at(name).pressState >= Input::PRESSED && window_focused;
}

bool Engine::is_input_held(const char* name) const {
    return input_map.at(name).pressState == Input::HELD && window_focused;
}

[[nodiscard]] Vec2 Engine::get_mouse_window_position() const {
    double cur_x{}, cur_y{};
    glfwGetCursorPos(glfw, &cur_x, &cur_y);
    return { cur_x, cur_y };
}

void Engine::set_window_size(const Vec2 &new_size) const {
    glfwSetWindowSize(glfw, (int) new_size.x, (int) new_size.y);
}

void Engine::set_window_size(const float x, const float y) const {
    glfwSetWindowSize(glfw, (int) x, (int) y);
}

void Engine::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        status = -1;
        return;
    }

    glfw = glfwCreateWindow((int) window_size.x, (int) window_size.y, title, nullptr, nullptr);
    if (!glfw) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        status = -1; // todo: use different codes for different errors
        return;
    }

    glfwMakeContextCurrent(glfw);
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context\n";
        glfwTerminate();
        status = -1;
    }
}

void Engine::start() {
    glfwSwapInterval(vsync ? 1 : target_framerate);
    vp_shader.create();
    vp_shader.use();
    _do_reshape_viewport_gl((int) window_size.x, (int) window_size.y);
    current_time = glfwGetTime();
    prev_time = current_time;
    
    // Load the default scene
    if (!current_scene) current_scene = default_scene;
    
    // begin event loop
    while (current_scene && !current_scene -> should_quit && !glfwWindowShouldClose(glfw)) {
        const double new_time = glfwGetTime();
        const double frame_time = new_time - current_time;
        current_time = new_time;
        elapsed_time += frame_time;
        accumulator += frame_time;
        
        // Register callbacks
        glfwSetFramebufferSizeCallback(glfw, _glfw_framebuffer_size_callback);
        glfwSetKeyCallback(glfw, _glfw_key_callback);
        glfwSetMouseButtonCallback(glfw, _glfw_mouse_button_callback);
        glfwSetCursorPosCallback(glfw, _glfw_cursor_pos_callback);
        
        // Events
        glfwPollEvents();
        
        // If the window isn't focused, limit framerate
        if (window_focused = glfwGetWindowAttrib(glfw, GLFW_FOCUSED); !window_focused) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(vsync ? 1 : target_framerate);  // Set the framerate back
        }
        
        update_world_bounds();
        
        // Update
        while (accumulator >= updates_per_frame) {
            if (current_scene -> update_enabled) {
                current_scene -> update_children();
                current_scene -> update(frame_time);
            }
            accumulator -= updates_per_frame;
        }
        
        // Draw
        if (current_scene -> draw_enabled) {
            current_scene -> draw_children();
            current_scene -> draw();
        }
        glfwSwapBuffers(glfw);

        // wait for the calculation to finish
        if (const double current_fps = _get_current_framerate(frame_count, prev_time); current_fps > 0) {
            fps = current_fps;
            std::cout << "fps: " << current_fps << "\n";
        }
    }
    
    std::cout << "Quitting...\n";
    glfwDestroyWindow(glfw);
    glfwTerminate();
    
    status = 0; // :)
}

// Initialize singleton
Engine *Engine::instance_ = nullptr;
