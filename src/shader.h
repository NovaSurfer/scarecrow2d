//
// Created by Maksim Ruts on 28-Aug-18.
//

#ifndef INC_2D_GAME_SHADER_H
#define INC_2D_GAME_SHADER_H

#include <iostream>
#include <map>
#include <glad/glad.h>


class Shader {
public:
    enum class ShaderType {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        NONE
    };
    const GLuint &get_program() const;
    Shader &run();
    void compile(const GLchar *vert_src, const GLchar *frag_src, const GLchar *geom_src = nullptr);
private:

    const std::map<ShaderType, GLenum> shader_types {
        {ShaderType::VERTEX,   GL_VERTEX_SHADER},
        {ShaderType::FRAGMENT, GL_FRAGMENT_SHADER},
        {ShaderType::GEOMETRY, GL_GEOMETRY_SHADER}
    };

    GLuint program;
    void error_checking(GLuint object, ShaderType shader_type = ShaderType::NONE);
    void make_shader(const GLchar *shader_src, GLuint &shader_obj, Shader::ShaderType shader_type);
};


#endif //INC_2D_GAME_SHADER_H
