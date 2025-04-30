#include "../../include/engine/Scene.h"

Scene::~Scene() {
    for (auto &[_, child]: children) {
        delete child;
    }
}

template<typename T>
Result<T*> Scene::get_child(const char* key) {
    if (!children.contains(key)) return Result<T*>(std::string("Object not found"));
    T *v = dynamic_cast<T*>(children.at(key));
    return Result<T*>(v);
}

void Scene::add_child(const std::string &name, SceneItem *child, int layer) {
    children.insert({ name, child });
    child -> scene = this;
    child -> parent = nullptr;
}

void Scene::remove_child(const std::string &name) {
    children.erase(name);
}

void Scene::draw_children() {
    for (auto [_, child]: children) {
        child -> gl_draw();
    }
}
