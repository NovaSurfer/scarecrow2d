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
        u32 instances_count;
    };

    struct renderable_2d : rend_data2d
    {
        void set_color(const colorRGB& color);
        void set_texture(const GLuint texid);
        void set_texture_array(const GLuint texid);
    };

    struct transformable_2d : renderable_2d
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

    struct obj2d : transformable_2d
    {
        obj2d* parent;
    };

}

#endif //SCARECROW2D_RENDERABLE_H
