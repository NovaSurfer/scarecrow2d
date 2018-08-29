//
// Created by Maksim Ruts on 28-Aug-18.
//

#include "shader.h"

const GLuint &Shader::get_program() const {
    return program;
}

Shader &Shader::run() {
    glUseProgram(program);
    return *this;
}

void Shader::compile(const GLchar *vert_src, const GLchar *frag_src, const GLchar *geom_src) {
    GLuint vert_obj{}, frag_obj{}, geom_obj{};

    // creating new shader program
    program = glCreateProgram();

    // Vertex shader
    make_shader(vert_src, vert_obj, ShaderType::VERTEX);
    glAttachShader(program, vert_obj);

    // Fragment shader
    make_shader(frag_src, frag_obj, ShaderType::FRAGMENT);
    glAttachShader(program, frag_obj);

    // Geometry shader
    if(geom_src != nullptr)
    {
        make_shader(geom_src, geom_obj, ShaderType::GEOMETRY);
        glAttachShader(program, geom_obj);
    }

    // Link program & check for linkage errors
    glLinkProgram(program);
    error_checking(program);

    // Cleaning
    glDeleteShader(vert_obj);
    glDeleteShader(frag_obj);
    glDeleteShader(geom_obj);

}

void Shader::make_shader(const GLchar *shader_src, GLuint shader_obj, Shader::ShaderType shader_type) {
    GLenum shader_t = shader_types.at(shader_type);
    shader_obj = glCreateShader(shader_t);
    glShaderSource(shader_obj, 1, &shader_src, nullptr);
    glCompileShader(shader_obj);
    error_checking(shader_obj, shader_type);
}

void Shader::error_checking(GLuint object, Shader::ShaderType shader_type) {
    GLint success = 0;
    GLchar error_log[1024];

    if(shader_type == ShaderType::NONE)
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, error_log);
            std::cout << "ERROR :: SHADER :: Compile-time error: " << error_log << '\n';
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, error_log);
            std::cout << "ERROR :: SHADER :: Link-time error: " << error_log << '\n';
        }
    }
}



