//
// Created by novasurfer on 7/1/19.
//

#include "texture_atlas.h"

namespace sc2d
{
    TextureAtlas::TextureAtlas(unsigned char* img_data, const GLuint width, const GLuint height,
                               const GLuint img_format)
        : data {img_data}
        , width {width}
        , height {height}
        , internal_format {img_format}
        , image_format {img_format}
        , wrap_s {GL_REPEAT}
        , wrap_t {GL_REPEAT}
        , filter_min {GL_LINEAR}
        , filter_max {GL_LINEAR}
    {
        generate();
    }

    void TextureAtlas::bind(const math::size2d& crop) const
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, obj_id);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internal_format, crop.width, crop.height, 0, 0,
                     internal_format, GL_UNSIGNED_BYTE, data);
    }

    const GLuint& TextureAtlas::get_obj_id() const
    {
        return obj_id;
    }

    void TextureAtlas::generate()
    {
        // generate texture
        glGenTextures(1, &obj_id);
        // create texture
        glBindTexture(GL_TEXTURE_2D_ARRAY, obj_id);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internal_format, width, height, 0, 0, internal_format,
                     GL_UNSIGNED_BYTE, data);
        // set wrap mode
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap_t);
        // set filter mode
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, filter_min);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, filter_max);
        // unbind texture
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }
}