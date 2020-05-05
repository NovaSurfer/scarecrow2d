//
// Created by novasurfer on 5/6/20.
//

#ifndef SCARECROW2D_RENDERABLE_H
#define SCARECROW2D_RENDERABLE_H

#include "rendering_types.h"
#include "shader.h"

namespace sc2d
{
    struct obj2d
    {
        obj2d() = default;
        obj2d(const obj2d&) = delete;
        obj2d& operator=(const obj2d&) = delete;

        void set_color(const colorRGB& color);
        void set_texture(const GLuint texid);
        void set_pos(const math::vec2& pos);
        void set_size(const math::vec2& size);
        void set_rot(const float rot);
        void set_transfdata(const math::vec2& pos, const math::vec2& size, const float rot);
        void set_transform(const math::mat4& transform);

        void update_transform();

        math::vec2 pos;
        math::vec2 size;
        float rot;
        math::mat4 transform;
        Shader shader;
        GLuint texid;
    };
}

#endif //SCARECROW2D_RENDERABLE_H
