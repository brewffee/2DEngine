#pragma once

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "2DEngine/color/RGBAColor.h"

class ShaderProgram {
    GLuint id{};
    const char* vertex_path;
    const char* frag_path;

    static GLuint load_shader(const char* path, GLenum type);

    public:
        ShaderProgram(const char* vertex_path, const char* frag_path); ~ShaderProgram();

        void create();
        void use() const;
        void set_uniform(const char* name, const glm::mat4 &matrix) const;
        void set_uniform(const char *name, const RGBAColor &cvec) const;
};
