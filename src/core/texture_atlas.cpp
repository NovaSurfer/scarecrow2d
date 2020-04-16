//
// Created by novasurfer on 7/1/19.
//

#include "texture_atlas.h"
#include "core/dbg/ogl_errors.h"

namespace sc2d
{
    TextureAtlas::TextureAtlas(unsigned char* img_data, const GLuint width, const GLuint height,
                               const GLuint rows, const GLuint columns, const GLuint img_format)
        : data {img_data}
        , width {width}
        , height {height}
        , rows {rows}
        , columns {columns}
        , internal_format {img_format}
        , image_format {img_format}
        , wrap_s {GL_REPEAT}
        , wrap_t {GL_REPEAT}
        , filter_min {GL_LINEAR}
        , filter_max {GL_LINEAR}
    {
        generate();
    }

    void TextureAtlas::bind() const
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, obj_id);
    }

    GLuint TextureAtlas::get_obj_id() const
    {
        return obj_id;
    }

    void TextureAtlas::generate()
    {
        const uint bytes_per_pixel = image_format == GL_RGB ? 3 : 4;
        const size_t tile_width = width / rows;
        const size_t tile_height = height / columns;
        const size_t tiles_length = rows * columns;
        const size_t next_row_offset = tile_width * tile_width;
        size_t ptr_offset = tile_width;

        glGenTextures(1, &obj_id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, obj_id);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
        glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, height);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, tile_width, tile_height, tiles_length, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        for(size_t i = 0; i < tiles_length; ++i) {
            if(i % rows == 0) {
                ptr_offset = next_row_offset * i;
            } else {
                ptr_offset += tile_width;
            }

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tile_width, tile_height, 1, GL_RGBA,
                            GL_UNSIGNED_BYTE, data + ptr_offset * bytes_per_pixel);
        }

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, filter_max);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, filter_min);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap_t);

        // unbind texture
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

        log_gl_error_cmd();
    }
}