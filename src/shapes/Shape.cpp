#include "../../include/shapes/Shape.h"

Shape::Shape(Transform *transform, RGBAColor color = RGBAColors::white) {
    this -> transform = transform;
    this -> color = color;
}
