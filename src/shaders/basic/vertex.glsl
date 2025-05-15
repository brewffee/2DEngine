#version 330 core

layout(location = 0) in vec2 pos;

uniform vec4 color_vec;
uniform mat4 trans_matrix;
uniform mat4 projection_matrix;

out vec4 vertex_color;

void main() {
    gl_Position = projection_matrix * trans_matrix * vec4(pos, 0.0, 1.0);
    vertex_color = color_vec;
}
