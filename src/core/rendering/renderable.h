//
// Created by novasurfer on 5/6/20.
//

#ifndef SCARECROW2D_RENDERABLE_H
#define SCARECROW2D_RENDERABLE_H

#include "rendering_types.h"
#include "shader.h"

namespace sc2d
{

    struct rend_data2d
    {
        Shader shader;
        GLuint texid;
        GLuint quad_vao;
        u32 layer;
    };

    template <typename T>
    struct default_renderable_2d : rend_data2d
    {
        void set_texture(const GLuint texid);
        void set_color(const colorRGB& color);
    };

    template <typename T>
    struct default_transformable_2d : default_renderable_2d<T>
    {
        void set_pos(const math::vec2& pos);
        void set_size(const math::vec2& size);
        void set_rot(const float rot);
        void set_transfdata(const math::vec2& pos, const math::vec2& size, const float rot, const math::mat4& projection);
        void set_transform(const math::mat4& transform);
        void set_projection(const math::mat4& projection);
        void update_transform();

        math::vec2 size;
        math::vec2 pos;
        float rot;
        math::mat4 transform;
        math::mat4 projection;
    };

    struct obj2d : default_transformable_2d<obj2d>
    { };

    struct obj2d_instatiable : default_transformable_2d<obj2d_instatiable>
    {
        size_t instances_count;
    };

}

#endif //SCARECROW2D_RENDERABLE_H
