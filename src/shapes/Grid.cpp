#include "../../include/shapes/Grid.h"

Grid::Grid(Transform *transform, RGBAColor color = RGBAColors::white, float interval = 0.f) {
    this -> transform = transform;
    this -> color = color;
    this -> interval = interval;
}

void Grid::gl_draw() {
    auto &[position, scale, rotation, center_origin] = *transform;
    auto &[el, er, et, eb] = Engine::instance() -> get_world_bounds();
    
    // draw only the axes
    if (interval == 0.f) {
        glLoadIdentity();
        glTranslatef(position.x, position.y, 0.f); // Apply the origin offset
        
        glLineWidth(1.f);
        glColor3f(RGB(color));
        glBegin(GL_LINES);
        
        // Horizontal
        glVertex2f(el, 0.f);
        glVertex2f(er, 0.f);
        
        // Vertical
        glVertex2f(0.f, et);
        glVertex2f(0.f, eb);
        
        glEnd();
    } else {
        // main grid
        glLoadIdentity();
        glTranslatef(position.x, position.y, 0.f); // Apply the origin offset
        
        glLineWidth(1.f);
        glColor3f(RGB(color));
        glBegin(GL_LINES);
        
        // Repeating horizontal lines
        for (auto y = (int) ceilf(eb / interval); y <= (int) floorf(et / interval); ++y) {
            glVertex2f(el, (float) y * interval);
            glVertex2f(er, (float) y * interval);
        }
        
        // Repeating vertical lines
        for (auto x = (int) ceilf(el / interval); x <= (int) floorf(er / interval); ++x) {
            glVertex2f((float) x * interval, et);
            glVertex2f((float) x * interval, eb);
        }
        
        glEnd();
    }
}
