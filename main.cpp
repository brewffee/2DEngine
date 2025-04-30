#include "include/color/RGBAColor.h"
#include "include/engine/Engine.h"
#include "include/engine/Scene.h"
#include "include/math/Vec2.h"
#include "include/shapes/Grid.h"
#include "include/shapes/QuadShape.h"

using namespace RGBAColors;

class MyScene final: public Scene {
    QuadShape* cursor;
    QuadShape* rectangle;
    QuadShape* player;
    float speed = .01f;
    
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
            auto &[wb_left, wb_right, wb_top, wb_bottom] = Engine::instance() -> get_world_bounds();
            
            wkeyd = new QuadShape(new Transform({ wb_right + .18f, wb_top - .08f }, Vec2::of(.1f)), white);
            akeyd = new QuadShape(new Transform({ wb_right + .08f, wb_top - .18f }, Vec2::of(.1f)), white);
            skeyd = new QuadShape(new Transform({ wb_right + .18f, wb_top - .18f }, Vec2::of(.1f)), white);
            dkeyd = new QuadShape(new Transform({ wb_right + .28f, wb_top - .18f }, Vec2::of(.1f)), white);
            lskeyd = new QuadShape(new Transform({ wb_right + .43f, wb_top - .08f }, Vec2::of(.1f)), white);
            
            add_child("w", wkeyd);
            add_child("a", akeyd);
            add_child("s", skeyd);
            add_child("d", dkeyd);
            add_child("ls", lskeyd);
            
            cursor = new QuadShape(Transform::from_scale(.05f), red);
            add_child("cursor", cursor);
            
            player = new QuadShape(Transform::from_scale(.125f), purple);
            add_child("player", player);
            
            rectangle = new QuadShape(Transform::from_scale(.2375f, .15f), orange);
            add_child("rectangle", rectangle);
            
            subGrid = new Grid(Transform::zero(), light_gray, .125f);
            mainGrid = new Grid(Transform::zero(), gray, .5f);
            axes = new Grid(Transform::zero(), white, 0.f);
            add_child("axes", axes);
            add_child("mainGrid", mainGrid);
            add_child("subGrid", subGrid);
        }

        ~MyScene() override = default;
        
        void update(double) override {
            // Moves according to what key is pressed
            if (p_up)       player -> transform -> position.y += speed * (p_sprint ? 2.f : 1.f);
            if (p_left)     player -> transform -> position.x -= speed * (p_sprint ? 2.f : 1.f);
            if (p_down)     player -> transform -> position.y -= speed * (p_sprint ? 2.f : 1.f);
            if (p_right)    player -> transform -> position.x += speed * (p_sprint ? 2.f : 1.f);
            
            auto &[wb_left, wb_right, wb_top, wb_bottom] = Engine::instance() -> get_world_bounds();
            const Vec2 mouse_pos = Engine::instance() -> get_mouse_pos();
            
            cursor -> transform = new Transform({ mouse_pos.x, mouse_pos.y }, Vec2::of(.05f), {});
            
            wkeyd -> color = p_up ? blue : white;
            akeyd -> color = p_left ? blue : white;
            skeyd -> color = p_down ? blue : white;
            dkeyd -> color = p_right ? blue : white;
            lskeyd -> color = p_sprint ? blue : white;
            
            wkeyd -> transform = new Transform({ wb_left+.18f, wb_top-.08f }, Vec2::of(.1f), {}, true);
            akeyd -> transform = new Transform({ wb_left+.07f, wb_top-.19f }, Vec2::of(.1f), {}, true);
            skeyd -> transform = new Transform({ wb_left+.18f, wb_top-.19f }, Vec2::of(.1f), {}, true);
            dkeyd -> transform = new Transform({ wb_left+.29f, wb_top-.19f }, Vec2::of(.1f), {}, true);
            lskeyd -> transform = new Transform({ wb_left+.40f, wb_top-.08f }, Vec2::of(.1f), {}, true);

            // todo: properly impl bounds + this is wroooong af
            const Vec2 rectPos = rectangle -> transform -> position;
            const Vec2 rectScale = rectangle -> transform -> scale;
            if (mouse_pos.x > rectPos.x
            && mouse_pos.x < rectPos.x + rectScale.x
            && mouse_pos.y > rectPos.y
            && mouse_pos.y < rectPos.y + rectScale.y) {
                rectangle -> color = blue;
            } else {
                rectangle -> color = orange;
            }
        }
        
        void draw() override {
            // todo: give scene a default color and draw before the children
            glClearColor(RGBA_F(RGBAColors::black));
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
                player->transform->position = Vec2::zero();
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
