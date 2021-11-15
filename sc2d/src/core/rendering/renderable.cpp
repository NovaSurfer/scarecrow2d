//
// Created by novasurfer on 5/6/20.
//

#include "renderable.h"
#include "math/transform.h"

namespace sc2d
{
    void renderable_2d::set_texture(GLuint texid)
    {
        this->texid = texid;
        shader.run();
        shader.set_int(shader_const::IMG, texid);
    }

    void renderable_2d::set_texture_array(const GLuint texid)
    {
        this->texid = texid;
        shader.run();
        shader.set_int(shader_const::IMG_ARRAY, texid);
    }

    void renderable_2d::set_color(const colorRGB& color)
    {
        shader.run();
        shader.set_vec3(shader_const::IMG_COLOR, color);
    }

    void transformable_2d::set_pos(const math::vec2& pos)
    {
        this->pos = pos;
        update_transform();
    }

    void transformable_2d::set_size(const math::vec2& size)
    {
        this->size = size;
        update_transform();
    }

    void transformable_2d::set_rot(const float rot)
    {
        this->rot = rot;
        update_transform();
    }

    void transformable_2d::set_transfdata(const math::vec2& pos, const math::vec2& size,
                                                     const float rot, const math::mat4& projection)
    {
        this->pos = pos;
        this->size = size;
        this->rot = rot;
        this->projection = projection;
        update_transform();
    }

    void transformable_2d::set_transform(const math::mat4& transform)
    {
        this->transform = transform;
        this->shader.run();
        this->shader.set_mat4(shader_const::MVP, transform * projection);
    }

    void transformable_2d::set_projection(const math::mat4& projection)
    {
        this->projection = projection;
        this->shader.run();
        this->shader.set_mat4(shader_const::MVP, transform * projection);
    }

    void transformable_2d::update_transform()
    {
        transform =
            math::transform(math::vec3(size.x, size.y, 1.0f), math::vec3(0.0f, 0.0f, 1.0f), rot,
                            math::vec3(0.5f * size.x + pos.x, 0.5f * size.y + pos.y, 0.0f));

        this->shader.run();
        this->shader.set_mat4(shader_const::MVP, transform * projection);
    }
}
