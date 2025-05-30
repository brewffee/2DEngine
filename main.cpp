#include "2DEngine/color/RGBAColor.h"
#include "2DEngine/engine/Engine.h"
#include "2DEngine/engine/Scene.h"
#include "2DEngine/math/Vec2.h"
#include "2DEngine/shapes/Grid.h"
#include "2DEngine/shapes/QuadShape.h"

using namespace RGBAColors;

enum Layers: uint8_t {
    UI_LAYER            = 4,
    MAIN_LAYER          = 2,
    BACKGROUND_LAYER    = 0
};

class MyScene final: public Scene {
    QuadShape *cursor, *rectangle, *player;
    Grid *axes, *mainGrid, *subGrid;
    QuadShape *wkeyd, *akeyd, *skeyd, *dkeyd, *lskeyd;
    QuadShape *etop, *ebottom, *eleft, *eright;

    float speed = .01f;
    bool p_up{}, p_down{}, p_left{}, p_right{}, p_sprint{};
    
    public:
        MyScene() { // todo: move to a ready() function, stupid !!!
            auto &[wb_left, wb_right, wb_top, wb_bottom] = Engine::instance() -> get_world_bounds();

            wkeyd = new QuadShape(new Transform({ wb_right + .18f, wb_top - .08f }, Vec2::of(.1f)), white);
            akeyd = new QuadShape(new Transform({ wb_right + .08f, wb_top - .18f }, Vec2::of(.1f)), white);
            skeyd = new QuadShape(new Transform({ wb_right + .18f, wb_top - .18f }, Vec2::of(.1f)), white);
            dkeyd = new QuadShape(new Transform({ wb_right + .28f, wb_top - .18f }, Vec2::of(.1f)), white);
            lskeyd = new QuadShape(new Transform({ wb_right + .43f, wb_top - .08f }, Vec2::of(.1f)), white);

            add_child(wkeyd, UI_LAYER);
            add_child(akeyd, UI_LAYER);
            add_child(skeyd, UI_LAYER);
            add_child(dkeyd, UI_LAYER);
            add_child(lskeyd, UI_LAYER);
            
            cursor = new QuadShape(Transform::from_scale(.05f), red);
            add_child(cursor, UI_LAYER);
            
            player = new QuadShape(Transform::from_scale(.25f), purple);
            add_child(player, MAIN_LAYER);
            
            rectangle = new QuadShape(Transform::from_scale(.2375f, .15f), orange);

            subGrid = new Grid(Transform::from_scale(wb_bottom, wb_right), light_gray, .125f);
            mainGrid = new Grid(Transform::from_scale(wb_top, wb_right), gray, .5f);
            axes = new Grid(Transform::from_scale(wb_top, wb_right), white, 0.f);
            axes -> set_line_width(2.f);

            add_child(subGrid, BACKGROUND_LAYER);
            add_child(mainGrid, BACKGROUND_LAYER);
            add_child(axes, BACKGROUND_LAYER);

            // like a compass
            etop = new QuadShape(new Transform({ 0.f, wb_top }, Vec2::of(.125f)), red);
            ebottom = new QuadShape(new Transform({ 0.f, wb_bottom }, Vec2::of(.125f)), white);
            eleft = new QuadShape(new Transform({ wb_left, 0.f }, Vec2::of(.125f)), white);
            eright = new QuadShape(new Transform({ wb_right, 0.f }, Vec2::of(.125f)), white);

            etop -> name = "etop";
            add_child(etop, UI_LAYER);
            add_child(ebottom, UI_LAYER);
            add_child(eleft, UI_LAYER);
            add_child(eright, UI_LAYER);
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
            
            wkeyd -> transform = new Transform({ wb_left+.18f, wb_top-.08f }, Vec2::of(.1f));
            akeyd -> transform = new Transform({ wb_left+.07f, wb_top-.19f }, Vec2::of(.1f));
            skeyd -> transform = new Transform({ wb_left+.18f, wb_top-.19f }, Vec2::of(.1f));
            dkeyd -> transform = new Transform({ wb_left+.29f, wb_top-.19f }, Vec2::of(.1f));
            lskeyd -> transform = new Transform({ wb_left+.40f, wb_top-.08f }, Vec2::of(.1f));

            subGrid -> transform = Transform::from_scale(1, 1);
            mainGrid -> transform = Transform::from_scale(1, 1);
            axes -> transform = Transform::from_scale(1, 1);

            etop -> transform = new Transform({ 0.f, wb_top }, Vec2::of(.125f));
            ebottom -> transform = new Transform({ 0.f, wb_bottom }, Vec2::of(.125f));
            eleft -> transform = new Transform({ wb_left, 0.f }, Vec2::of(.125f));
            eright -> transform = new Transform({ wb_right, 0.f }, Vec2::of(.125f));

            if (player -> transform -> bounds.contains(mouse_pos)) {
                player -> color = blue;
            } else {
                player -> color = purple;
            }
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
                player -> transform -> position = Vec2::zero();
            }

            if (Engine::instance() -> is_input_pressed("debug")) {
                remove_child("etop");
            }
        }
};

int main() {
    Engine *engine = Engine::instance();
    engine -> set_title("2D Engine");
    engine -> set_scale_mode(ScaleMode::KEEP);
    engine -> init();

    engine -> add_input({ "up", { GLFW_KEY_W } });
    engine -> add_input({ "down", { GLFW_KEY_S } });
    engine -> add_input({ "left", { GLFW_KEY_A } });
    engine -> add_input({ "right", { GLFW_KEY_D } });
    engine -> add_input({ "sprint", { GLFW_KEY_LEFT_SHIFT } });
    engine -> add_input({ "quit", { GLFW_KEY_ESCAPE } });
    engine -> add_input({ "reset", { GLFW_KEY_R } });
    engine -> add_input({ "debug", { GLFW_KEY_TAB } });

    MyScene scene;
    scene.set_background_color(black);
    engine -> set_default_scene(&scene);

    // todo: return an exit code from start() instead
    engine -> start();
    return EXIT_SUCCESS; // :D
}
