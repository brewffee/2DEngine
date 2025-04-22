#include "include/math/Vec2.h"
#include "include/color/RGBAColor.h"
#include "include/engine/Scene.h"
#include "include/shapes/QuadShape.h"
#include "include/shapes/Grid.h"
#include "include/engine/Engine.h"

using namespace RGBAColors;

class MyScene final: public Scene {
    QuadShape* betterObj;
    QuadShape* redman;
    QuadShape* rectangularBangular;
    QuadShape* duude;
    float speed = 0.01f;
    
    Grid* axes;
    Grid* mainGrid;
    Grid* subGrid;

    QuadShape* wkeyd;
    QuadShape* akeyd;
    QuadShape* skeyd;
    QuadShape* dkeyd;
    QuadShape* lskeyd;

    bool p_up{}, p_down{}, p_left{}, p_right{}, p_sprint{};
    
    public:
        MyScene() {
            auto &[el, er, et, eb] = Engine::instance() -> get_world_bounds();
            
            wkeyd = new QuadShape(new Transform({er+.19f, et-.08f}, Vec2{0.1f}), RGBAColors::white);
            akeyd = new QuadShape(new Transform({er+.08f, et-.19f}, Vec2{0.1f}), RGBAColors::white);
            skeyd = new QuadShape(new Transform({er+.19f, et-.19f}, Vec2{0.1f}), RGBAColors::white);
            dkeyd = new QuadShape(new Transform({er+.31f, et-.19f}, Vec2{0.1f}), RGBAColors::white);
            lskeyd = new QuadShape(new Transform({er+.43f, et-.08f}, Vec2{0.1f}), RGBAColors::white);
            
            add_child("w", wkeyd);
            add_child("a", akeyd);
            add_child("s", skeyd);
            add_child("d", dkeyd);
            add_child("ls", lskeyd);
            
            duude = new QuadShape(Transform::from_scale(0.125f), purple);
            add_child("duude", duude);
            
            redman = new QuadShape(Transform::from_scale(0.05f), red);
            add_child("redman", redman);
            
            betterObj = new QuadShape(Transform::from_scale(0.075f), green);
            add_child("betterObj", betterObj);
            
            rectangularBangular = new QuadShape(Transform::from_scale(0.2375f, 0.15f), orange);
            add_child("rectangularBangular", rectangularBangular);
            
            subGrid = new Grid(Transform::zero(), light_gray, .125f);
            mainGrid = new Grid(Transform::zero(), gray, .5f);
            axes = new Grid(Transform::zero(), white, 0.f);
            
            add_child("subGrid", subGrid);
            add_child("mainGrid", mainGrid);
            add_child("axes", axes);
        };

        ~MyScene() override = default;
        
        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "cert-msc50-cpp"
        void update(double delta) override {
            // Moves according to what key is pressed
            if (p_up) duude->transform->position.y += speed * (p_sprint ? 2.f : 1.f);
            if (p_left) duude->transform->position.x -= speed * (p_sprint ? 2.f : 1.f);
            if (p_down) duude->transform->position.y -= speed * (p_sprint ? 2.f : 1.f);
            if (p_right) duude->transform->position.x += speed * (p_sprint ? 2.f : 1.f);
            
            auto &[el, er, et, eb] = Engine::instance() -> get_world_bounds();
            Vec2 mouse_pos = Engine::instance() -> get_mouse_pos();

            redman->transform = new Transform({mouse_pos.x, mouse_pos.y}, Vec2{0.05f}, {});
            
            auto &[position, scale, rotation, _] = *betterObj -> transform;
            float new_x = position.x + (((delta) *(rand() % 100 - 50) / 10));
            float new_y = position.y + (((delta) *(rand() % 100 - 50) / 10));
            if (new_x < er && new_x > el) position.x = new_x;
            if (new_y > eb && new_y < et) position.y = new_y;
            scale.x += (rand() % 100 - 50) / rand();
            scale.y += (rand() % 100 - 50) / rand();
            
            wkeyd -> color = p_up ? RGBAColors::blue : RGBAColors::white;
            akeyd -> color = p_left ? RGBAColors::blue : RGBAColors::white;
            skeyd -> color = p_down ? RGBAColors::blue : RGBAColors::white;
            dkeyd -> color = p_right ? RGBAColors::blue : RGBAColors::white;
            lskeyd -> color = p_sprint ? RGBAColors::blue : RGBAColors::white;
            
            wkeyd -> transform = new Transform({el+.19f, et-.08f}, Vec2{0.1f}, {}, true);
            akeyd -> transform = new Transform({el+.08f, et-.19f}, Vec2{0.1f}, {}, true);
            skeyd -> transform = new Transform({el+.19f, et-.19f}, Vec2{0.1f}, {}, true);
            dkeyd -> transform = new Transform({el+.31f, et-.19f}, Vec2{0.1f}, {}, true);
            lskeyd -> transform = new Transform({el+.43f, et-.08f}, Vec2{0.1f}, {}, true);
            
            // If the mouse is over rectangularBangular, change its color
            // todo: properly impl bounds + this is wroooong af
            Vec2 rectPos = rectangularBangular -> transform -> position;
            Vec2 rectScale = rectangularBangular -> transform -> scale;
            if (mouse_pos.x > rectPos.x
            && mouse_pos.x < rectPos.x + rectScale.x
            && mouse_pos.y > rectPos.y
            && mouse_pos.y < rectPos.y + rectScale.y) {
                rectangularBangular -> color = RGBAColors::blue;
            } else {
                rectangularBangular -> color = RGBAColors::orange;
            }
        }
        #pragma clang diagnostic pop
        
        void draw() override {
            
            // todo: give scene a default color and draw before the children
            glClearColor(RGBA(RGBAColors::black));
            glClear(GL_COLOR_BUFFER_BIT);
            
            draw_children();
        }
        
        // todo: pass input as a param instead of having to access singleton directly
        void input() override {
            p_up = Engine::instance() -> is_input_pressed("up");
            p_down = Engine::instance() -> is_input_pressed("down");
            p_left = Engine::instance() -> is_input_pressed("left");
            p_right = Engine::instance() -> is_input_pressed("right");
            p_sprint = Engine::instance() -> is_input_pressed("sprint");
            
            should_quit = Engine::instance() -> is_input_pressed("quit");
            
            if (Engine::instance() -> is_input_pressed("reset")) {
                duude->transform->position = Vec2{0};
            }
        }
};

int main() {
    MyScene scene;
    
    Engine::instance() -> add_input({ "up", { GLFW_KEY_W } });
    Engine::instance() -> add_input({ "down", { GLFW_KEY_S } });
    Engine::instance() -> add_input({ "left", { GLFW_KEY_A } });
    Engine::instance() -> add_input({ "right", { GLFW_KEY_D } });
    Engine::instance() -> add_input({ "sprint", { GLFW_KEY_LEFT_SHIFT } });
    Engine::instance() -> add_input({ "quit", { GLFW_KEY_ESCAPE } });
    Engine::instance() -> add_input({ "reset", { GLFW_KEY_R } });
    
    Engine::instance() -> set_default_scene(&scene);
    Engine::instance() -> start();
    
    return EXIT_SUCCESS; // :D
}
