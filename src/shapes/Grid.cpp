#include "2DEngine/shapes/Grid.h"

#include <vector>
#include <glad/gl.h>

struct VertexData { //todo: move to somewhere more appropriate
    Vec2 position;
    RGBAColor color;
};

Grid::Grid(Transform *transform, const RGBAColor &color = RGBAColors::white, const float interval = 0.f): color(color) {
    this -> transform = transform;
    this -> interval = interval;
    this -> shader.create();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // will alloc to max_vertices so it has enough space
    // sometimes the entire grid will not be drawn if the interval is too large, user will need
    // to increase max vertices count
    // todo: could we just calculate based off the interval? what happens if the user wants to increase it??
    //    find some sort of solution for this
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, max_vertices * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);

    // position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

void Grid::gl_draw() {
    auto &[position, scale, rotation, _c, _v] = *transform;

    Vector<VertexData> line_data;

    auto &[el, er, et, eb] = Engine::instance() -> get_world_bounds();
    const glm::mat4 &projection_matrix = Engine::instance() -> get_projection_matrix();

    if (interval <= 0.f) {
        // axis lines
        line_data = {
            /* LR */ { Vec2(er, 0.f), color }, { Vec2(el, 0.f), color },
            /* TB */ { Vec2(0.f, et), color }, { Vec2(0.f, eb), color }
        };
    } else {
        // main
        for (auto y = (int) ceilf(eb / interval); y <= (int) floorf(et / interval); ++y) {
            line_data.push_back({ Vec2(el, (float) y * interval), color });
            line_data.push_back({ Vec2(er, (float) y * interval), color });
        }

        for (auto x = (int) ceilf(el / interval); x <= (int) floorf(er / interval); ++x) {
            line_data.push_back({ Vec2((float) x * interval, eb), color });
            line_data.push_back({ Vec2((float) x * interval, et), color });
        }
    }

    // push to vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, line_data.size() * sizeof(VertexData), line_data.data());

    // trans
    glm::mat4 trans_matrix(1.0f);
    trans_matrix = glm::translate(trans_matrix, glm::vec3(position.x, position.y, 0.0f));
    trans_matrix = glm::scale(trans_matrix, glm::vec3(scale.x, scale.y, 1.0f));
    trans_matrix = glm::rotate(trans_matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Load and set shader properties
    shader.use();
    shader.set_uniform("color_vec", color); // todo: support gradients
    shader.set_uniform("trans_matrix", trans_matrix);
    shader.set_uniform("projection_matrix", projection_matrix);

    // Render lines
    glBindVertexArray(vao);
    glLineWidth(line_width);
    glDrawArrays(GL_LINES, 0, line_data.size());
    glBindVertexArray(0);
}
