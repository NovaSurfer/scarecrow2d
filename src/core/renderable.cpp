//
// Created by novasurfer on 5/6/20.
//

#include "renderable.h"
#include "math/transform.h"

namespace sc2d
{

    template class default_renderable_2d<obj2d>;
    template class default_renderable_2d<obj2d_instatiable>;
    template class default_renderable_2d<text2d>;
    template class default_transformable_2d<obj2d>;
    template class default_transformable_2d<obj2d_instatiable>;

    template <typename T>
    void default_renderable_2d<T>::set_texture(GLuint texid)
    {
        this->texid = texid;
        shader.run();
        if constexpr(std::is_same<T, obj2d>::value || std::is_same<T, text2d>::value) {
            shader.set_int(shader_const::IMG, texid);
        } else {
            shader.set_int(shader_const::IMG_ARRAY, texid);
        }
    }

    template <typename T>
    void default_renderable_2d<T>::set_color(const colorRGB& color)
    {
        shader.run();
        shader.set_vec3(shader_const::IMG_COLOR, color);
    }

    template <typename T>
    void default_transformable_2d<T>::set_pos(const math::vec2& pos)
    {
        this->pos = pos;
        update_transform();
    }

    template <typename T>
    void default_transformable_2d<T>::set_size(const math::vec2& size)
    {
        this->size = size;
        update_transform();
    }

    template <typename T>
    void default_transformable_2d<T>::set_rot(const float rot)
    {
        this->rot = rot;
        update_transform();
    }

    template <typename T>
    void default_transformable_2d<T>::set_transfdata(const math::vec2& pos, const math::vec2& size,
                                                     const float rot)
    {
        this->pos = pos;
        this->size = size;
        this->rot = rot;
        update_transform();
    }

    template <typename T>
    void default_transformable_2d<T>::set_transform(const math::mat4& transform)
    {
        this->transform = transform;
        this->shader.run();
        this->shader.set_mat4(shader_const::MODEL, transform);
    }

    template <typename T>
    void default_transformable_2d<T>::update_transform()
    {
        transform =
            math::transform(math::vec3(size.x, size.y, 1.0f), math::vec3(0.0f, 0.0f, 1.0f), rot,
                            math::vec3(0.5f * size.x + pos.x, 0.5f * size.y + pos.y, 0.0f));

        this->shader.run();
        this->shader.set_mat4(shader_const::MODEL, transform);
    }
}
