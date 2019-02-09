//
// Created by Maksim Ruts on 28-Aug-18.
//

#ifndef INC_2D_GAME_SHADER_H
#define INC_2D_GAME_SHADER_H

#include <map>
#include <glad/glad.h>
#include "math/matrix4.h"
#include "math/vector3.h"

enum class ShaderType
{
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    NONE
};

class Shader {
public:
    const GLuint &get_program() const;
    Shader &run();
    void compile(const GLchar *vert_src, const GLchar *frag_src, const GLchar *geom_src = nullptr);

    void set_mat4(const GLchar *name, const math::mat4 &matrix) const;
    void set_vec3(const GLchar *name, const math::vec3 &value) const;
    void set_int(const GLchar *name, GLint value) const;
private:
    static const std::map<ShaderType, GLenum> shader_types;
    GLuint program;
    
    void error_checking(GLuint object, ShaderType shader_type = ShaderType::NONE);
    void make_shader(const GLchar *shader_src, GLuint &shader_obj, ShaderType shader_type);
};


#endif //INC_2D_GAME_SHADER_H
