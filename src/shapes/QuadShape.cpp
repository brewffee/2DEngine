#include "../../include/shapes/QuadShape.h"

QuadShape::QuadShape(Transform *transform, const RGBAColor &color = RGBAColors::white) {
    this -> transform = transform;
    this -> color = color;
}

void QuadShape::gl_draw() {
    auto &[position, scale, rotation, center_origin] = *transform;
    
    glLoadIdentity();
    glRotatef(rotation.x, 1, 0, 0);
    glRotatef(rotation.y, 0, 1, 0);
    glRotatef(rotation.z, 0, 0, 1);
    
    glBegin(draw_mode);
    glColor3d(RGB(color));
    
    float dest_x{}, dest_y{};
    if (center_origin) {
        const Vec2 offset = scale / 2.f;
        dest_x = position.x - offset.x, dest_y = position.y - offset.y;
    } else dest_x = position.x, dest_y = position.y;
    
    glVertex2f(dest_x, dest_y);                     // bottom left
    glVertex2f(dest_x + scale.x, dest_y);           // bottom right
    glVertex2f(dest_x + scale.x, dest_y + scale.y); // top right
    glVertex2f(dest_x, dest_y + scale.y);           // top left
    glEnd();
}
