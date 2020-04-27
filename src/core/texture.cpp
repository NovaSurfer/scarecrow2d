//
// Created by Maksim Ruts on 29-Aug-18.
//

#include "texture.h"

namespace sc2d
{
    Texture2d::Texture2d(unsigned char* img_data, const GLuint width, const GLuint height,
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

    void Texture2d::generate()
    {
        // generate texture
        glGenTextures(1, &obj_id);
        // create texture
        glBindTexture(GL_TEXTURE_2D, obj_id);
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format,
                     GL_UNSIGNED_BYTE, data);
        // set wrap mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
        // set filter mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);
        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2d::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, obj_id);
    }
}
