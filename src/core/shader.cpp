//
// Created by Maksim Ruts on 28-Aug-18.
//

#include "shader.h"
#include "log2.h"
namespace sc2d
{

    GLuint Shader::get_program() const
    {
        return program;
    }

    const Shader& Shader::run() const
    {
        glUseProgram(program);
        return *this;
    }

    void Shader::compile(const GLchar* vert_src, const GLchar* frag_src, const GLchar* geom_src)
    {
        GLuint vert_obj;
        GLuint frag_obj;
        GLuint geom_obj;

        make_shader(vert_src, vert_obj, shader_t::VERTEX);
        make_shader(frag_src, frag_obj, shader_t::FRAGMENT);
        if(geom_src != nullptr)
            make_shader(geom_src, geom_obj, shader_t::GEOMETRY);

        // creating new shader program & attaching shaders to it
        program = glCreateProgram();
        glAttachShader(program, vert_obj);
        glAttachShader(program, frag_obj);
        if(geom_src != nullptr)
            glAttachShader(program, geom_obj);

        // Link program & check for linkage errors
        glLinkProgram(program);
        error_checking(program, shader_t::NONE);

        // After linking we dont need our shaders anymore
        glDetachShader(program, vert_obj);
        glDetachShader(program, frag_obj);
        if(geom_src != nullptr)
            glDetachShader(program, geom_obj);
        glDeleteShader(vert_obj);
        glDeleteShader(frag_obj);
        glDeleteShader(geom_obj);
    }

    void Shader::make_shader(const GLchar* shader_src, GLuint& shader_obj,
                             shader_t shader_type) const
    {
        shader_obj = glCreateShader(shader_type);
        glShaderSource(shader_obj, 1, &shader_src, nullptr);
        glCompileShader(shader_obj);
        error_checking(shader_obj, shader_type);
    }

    void Shader::error_checking(GLuint object, shader_t shader_type) const
    {
        GLint success = 0;
        GLchar error_log[1024];

        if(shader_type != shader_t::NONE) {
            // Check shaders for compile time errors
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(object, 1024, nullptr, error_log);
                log_err_cmd("SHADER :: Compile-time error: %s ", error_log);
            }
        } else {
            // Check shader program for link time errors
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(object, 1024, nullptr, error_log);
                log_err_cmd("SHADER :: Link-time error: %s", error_log);
            }
        }
    }

    void Shader::set_mat4(const GLchar* name, const math::mat4& matrix) const
    {
//        log_warn_cmd("%d", glGetUniformLocation(program, name));
        glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE,
                           (GLfloat*)&matrix.n[0][0]);
    }

    void Shader::set_vec3(const GLchar* name, const math::vec3& value) const
    {
//        log_warn_cmd("%d", glGetUniformLocation(program, name));
        glUniform3f(glGetUniformLocation(program, name), value.x, value.y, value.z);
    }

    void Shader::set_vec2(const GLchar* name, const math::vec2& value) const
    {
        glUniform2f(glGetUniformLocation(program, name), value.x, value.y);
    }

    void Shader::set_int(const GLchar* name, GLint value) const
    {
        glUniform1i(glGetUniformLocation(program, name), value);
    }

    void Shader::set_uint(const GLchar* name, GLuint value) const
    {
        glUniform1ui(glGetUniformLocation(program, name), value);
    }
}
