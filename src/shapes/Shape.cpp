#include "2DEngine/shapes/Shape.h"

Shape::Shape(Transform *transform, const RGBAColor &color = RGBAColors::white) {
    this -> transform = transform;
    this -> color = color;
}
