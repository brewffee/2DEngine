#include "2DEngine/engine/SceneItem.h"

SceneItem::SceneItem(Transform *transform) {
    this -> transform = transform;
}

SceneItem::~SceneItem() {
    delete transform;
}
