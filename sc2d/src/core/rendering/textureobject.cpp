//
// Created by novasurfer on 8/22/20.
//

#include "textureobject.h"
#include "core/types.h"
#include <type_traits>

namespace sc2d
{

    default_tex2d::default_tex2d(const GLuint width, const GLuint height,
                                 const GLuint internal_format, const GLuint image_format,
                                 const GLuint wrap_s, const GLuint wrap_t, const GLuint filter_min,
                                 const GLuint filter_max, unsigned char* img_data)
        : width {width}
        , height {height}
        , internal_format {internal_format}
        , image_format {image_format}
        , wrap_s {wrap_s}
        , wrap_t {wrap_t}
        , filter_min {filter_min}
        , filter_max {filter_max}
        , data {img_data}
    {
        texgen::generate(this);
    }

    default_tex2darr::default_tex2darr(const GLuint width, const GLuint height,
                                       const GLuint internal_format, const GLuint image_format,
                                       const GLuint wrap_s, const GLuint wrap_t,
                                       const GLuint filter_min, const GLuint filter_max,
                                       unsigned char* img_data, GLuint rows, GLuint columns)
        : default_tex2d {width,  height,     internal_format, image_format, wrap_s,
                         wrap_t, filter_min, filter_max,      img_data}
        , rows {rows}
        , columns {columns}

    {
        texgen::generate(this);
    }

    template <typename T>
    void texgen::generate(T* texdata)
    {
        GLuint texture_type;
        glGenTextures(1, &texdata->obj_id);

        // TEXTURE 2D
        if constexpr(std::is_same<T, default_tex2d>::value) {
            texture_type = GL_TEXTURE_2D;

            glBindTexture(GL_TEXTURE_2D, texdata->obj_id);
            glTexImage2D(GL_TEXTURE_2D, 0, texdata->internal_format, texdata->width,
                         texdata->height, 0, texdata->image_format, GL_UNSIGNED_BYTE,
                         texdata->data);
        }
        // TEXTURE 2D ARRAY
        if constexpr(std::is_same<T, default_tex2darr>::value) {
            texture_type = GL_TEXTURE_2D_ARRAY;

            const u32 bytes_per_channel = texdata->image_format == GL_RGB ? 3 : 4;
            const size_t tile_width = texdata->width / texdata->rows;
            const size_t tile_height = texdata->height / texdata->columns;
            const size_t tiles_length = texdata->rows * texdata->columns;
            const size_t next_row_offset = tile_width * tile_width;
            size_t ptr_offset = tile_width;

            glBindTexture(GL_TEXTURE_2D_ARRAY, texdata->obj_id);
            glPixelStorei(GL_UNPACK_ROW_LENGTH, texdata->width);
            glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, texdata->height);
            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, texdata->internal_format, tile_width, tile_height,
                         tiles_length, 0, texdata->image_format, GL_UNSIGNED_BYTE, nullptr);

            for(size_t i = 0; i < tiles_length; ++i) {
                if(i % texdata->rows == 0) {
                    ptr_offset = next_row_offset * i;
                } else {
                    ptr_offset += tile_width;
                }
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tile_width, tile_height, 1,
                                GL_RGBA, GL_UNSIGNED_BYTE,
                                texdata->data + ptr_offset * bytes_per_channel);
            }
        }

        glTexParameteri(texture_type, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(texture_type, GL_TEXTURE_MAX_LEVEL, 1);
        glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, texdata->filter_max);
        glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, texdata->filter_min);
        glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, texdata->wrap_s);
        glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, texdata->wrap_t);

        // unbind texture
        glBindTexture(texture_type, 0);
    }
}