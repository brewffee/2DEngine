#include "2DEngine/shapes/QuadShape.h"
#include <glad/gl.h>

#include "2DEngine/engine/Engine.h"

struct alignas(8) VertexData {
    Vec2 position;
    RGBAColor color = RGBAColors::white;
};

QuadShape::QuadShape(Transform *transform, const RGBAColor &color) {
    this -> transform = transform;
    this -> color = color;
    this -> shader.create();

    const Vector<VertexData> vertex_data = {
        { Vec2(-.5f, -.5f),   color },
        { Vec2(.5f, -.5f),    color },
        { Vec2(.5f, .5f),     color },
        { Vec2(-.5f, .5f),    color }
    };

    // generate vao/vbo
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexData), (GLvoid*) vertex_data.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void QuadShape::gl_draw() {
    auto &[position, scale, rotation, center, _] = *transform;
    const glm::mat4 &projection_matrix = Engine::instance() -> get_projection_matrix();

    // Calculate transformation matrix (todo: create own matrix class)
    auto trans_matrix = glm::mat4(1.0f);
    if (center) trans_matrix = glm::translate(trans_matrix, glm::vec3(position.x, position.y, 0.0f));
    else trans_matrix = glm::translate(trans_matrix, glm::vec3(position.x - scale.x / 2.f, position.y - scale.y / 2.f, 0.0f));
    trans_matrix = glm::scale(trans_matrix, glm::vec3(scale.x, scale.y, 1.0f));
    trans_matrix = glm::rotate(trans_matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Load and set shader properties
    shader.use();
    shader.set_uniform("color_vec", color); // todo: support gradients
    shader.set_uniform("trans_matrix", trans_matrix);
    shader.set_uniform("projection_matrix", projection_matrix);

    // Render square
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
