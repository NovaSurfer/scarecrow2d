//
// Created by novasurfer on 5/6/20.
//

#include "renderable.h"
#include "math/transform.h"

namespace sc2d
{

    void obj2d::set_color(const colorRGB& color)
    {
        shader.run();
        shader.set_vec3(shader_const::IMG_COLOR, color);
    }

    void obj2d::set_texture(const GLuint texid)
    {
        this->texid = texid;
        shader.run();
        shader.set_int(shader_const::IMG, texid);
    }

    void obj2d::set_pos(const math::vec2& pos)
    {
        this->pos = pos;
        update_transform();
    }

    void obj2d::set_size(const math::vec2& size)
    {
        this->size = size;
        update_transform();
    }

    void obj2d::set_rot(const float rot)
    {
        this->rot = rot;
        update_transform();
    }

    void obj2d::set_transfdata(const math::vec2& pos, const math::vec2& size, const float rot)
    {
        this->pos = pos;
        this->size = size;
        this->rot = rot;
        update_transform();
    }
    void obj2d::set_transform(const math::mat4& transform)
    {
        this->transform = transform;
    }
    void obj2d::update_transform()
    {
        transform = math::transform(
            math::vec3(size.x, size.y, 1.0f), math::vec3(0.0f, 0.0f, 1.0f), rot,
            math::vec3(0.5f * size.x + pos.x, 0.5f * size.y + pos.y, 0.0f));

        shader.run();
        shader.set_mat4(shader_const::MODEL, transform);
    }
}
