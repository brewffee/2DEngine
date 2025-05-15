#include "2DEngine/shaders/ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "2DEngine/color/RGBAColor.h"

GLuint ShaderProgram::load_shader(const char* path, GLenum type) {
    const std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string source = buffer.str();
    const char* source_str = source.c_str();

    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source_str, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log_buf[512];
        glGetShaderInfoLog(shader, 512, nullptr, log_buf);
        std::cerr << "Failed to compile shader " << path  << '\n' << log_buf << '\n';
    }

    return shader;
}

// //////////////////////////////////////////////////////////////////////////////////////////

ShaderProgram::ShaderProgram(const char* vertex_path, const char* frag_path):
    vertex_path(vertex_path),
    frag_path(frag_path) {}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

// //////////////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::create() {
    const GLuint vertex_shader = load_shader(vertex_path, GL_VERTEX_SHADER);
    const GLuint frag_shader = load_shader(frag_path, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, frag_shader);
    glLinkProgram(id);

    int success{};
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char log_buf[512];
        glGetProgramInfoLog(id, 512, nullptr, log_buf);
        std::cerr << "Failed to link shader program " << vertex_path << " and " << frag_path << '\n' << log_buf << '\n';
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

void ShaderProgram::set_uniform(const char* name, const glm::mat4 &matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, &matrix[0][0]);
}

void ShaderProgram::set_uniform(const char* name, const RGBAColor &cvec) const {
    glUniform4f(glGetUniformLocation(id, name), cvec.r, cvec.g, cvec.b, cvec.a);
}
