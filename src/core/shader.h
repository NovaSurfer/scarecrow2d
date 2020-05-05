//
// Created by Maksim Ruts on 28-Aug-18.
//

#ifndef INC_2D_GAME_SHADER_H
#define INC_2D_GAME_SHADER_H

#include "math/matrix4.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include <glad/glad.h>

namespace sc2d
{
    struct ShaderType
    {
        enum
        {
            NONE = -1,
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
            GEOMETRY = GL_GEOMETRY_SHADER
        };
    };

    // Instantiating anonymous enum
    using shader_t = decltype(ShaderType::NONE);

    namespace shader_const
    {
        constexpr char* IMG {"img"};
        constexpr char* IMG_COLOR {"img_color"};
        constexpr char* MODEL {"model"};
    }

    class Shader
    {
        friend class ShaderUtil;
    public:
        GLuint get_program() const;
        const Shader& run() const;
//        void compile(const GLchar* vert_src, const GLchar* frag_src,
//                     const GLchar* geom_src = nullptr);

        void set_mat4(const GLchar* name, const math::mat4& matrix) const;
        void set_vec3(const GLchar* name, const math::vec3& value) const;
        void set_vec2(const GLchar* name, const math::vec2& value) const;
        void set_int(const GLchar* name, GLint value) const;
        void set_uint(const GLchar* name, GLuint value) const;

        operator GLuint() const
        {
            return program;
        }

    private:
        GLuint program;

//        void error_checking(GLuint object, shader_t shader_type) const;
//        void make_shader(const GLchar* shader_src, GLuint& shader_obj, shader_t shader_type) const;
    };

    struct ShaderUtil
    {
        static void compile(Shader& shader, const GLchar* vert_src, const GLchar* frag_src,
                            const GLchar* geom_src);

    private:
        static void error_checking(GLuint object, shader_t shader_type);
        static void make_shader(const GLchar* shader_src, GLuint& shader_obj, shader_t shader_type);

    };
}
#endif //INC_2D_GAME_SHADER_H
