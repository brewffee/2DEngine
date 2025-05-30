#include "2DEngine/engine/Scene.h"

#include <GLFW/glfw3.h>

Scene::Scene() = default;

Scene::~Scene() {
    for (auto &[_, layer]: children) {
        for (auto const *child: layer) {
            delete child;
        }
    }
}
// //////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
Result<T*> Scene::get_child(const char* key) {
    for (auto &[_, layer]: children) {
        for (auto const *child: layer) {
            if (child -> name == key) {
                T *v = dynamic_cast<T*>(child);
                return Result<T*>(v);
            }
        }
    }

    return Result<T*>("Object not found");
}

void Scene::add_child(SceneItem *child, const int layer) {
    children[layer].push_back(child);
    child -> scene = this;
    child -> parent = nullptr;
}

void Scene::remove_child(const std::string &name) {
    for (auto &[_, layer]: children) {
        for (auto &child: layer) {
            if (child -> name == name) {
                if (const Result index = layer.index_of(child); index.ok()) {
                    layer.erase(index.value());
                }
            }
        }
    }
}

void Scene::update_children() {
    for (auto &[_, layer]: children) {
        for (const auto *child: layer) {
            child -> transform -> update_bounds();
            // todo: child -> update();
        }
    }
}

void Scene::draw_children() {
    glClearColor(RGBA(background_color));
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &[_, layer]: children) {
        for (const auto child: layer) {
            child -> gl_draw();
        }
    }
}
