//
// Created by novasurfer on 12/31/19.
//

#include "text_ft2.h"
#include "debug_utils.h"
#include "log2.h"
#include "math/utils.h"
#include <math/transform.h>

namespace sc2d
{
    Vertex TextFt2::quad_vertices[VERTICES_PER_QUAD] {SPRITE_QUAD.tr, SPRITE_QUAD.br,
                                                      SPRITE_QUAD.bl, SPRITE_QUAD.tl};

    void Ft2Font128::init(const char* font_path, uint8_t font_size)
    {

        height = font_size;

        if(FT_Init_FreeType(&ft))
            log_err_cmd("CAN NOT INIT FREETYPE.");

        FT_Face face;

        if(FT_New_Face(ft, font_path, 0, &face))
            log_info_cmd("FAILED TO LOAD FONT.");

        FT_Set_Pixel_Sizes(face, 0, font_size);

        // quick and dirty max texture size estimate
        uint32_t max_dim = (1 + (face->size->metrics.height >> 6)) * ceilf(sqrtf(128));
        tex_width = 1;
        while(tex_width < max_dim)
            tex_width <<= 1;
        uint32_t tex_height = tex_width;

        // render glyphs to atlas
        pixels = (unsigned char*)calloc(tex_width * tex_height, 1);
        uint32_t pen_x = 0, pen_y = 0;

        for(uint8_t i = 32; i < 128; ++i) {
            // Maybe its better to use FL_LOAD_TARGET_LIGHT for regular, non-pixelart fonts.
            FT_Load_Char(face, i, FT_LOAD_RENDER);
            FT_Bitmap* bmp = &face->glyph->bitmap;

            if(pen_x + bmp->width >= tex_width) {
                pen_x = 0;
                pen_y += ((face->size->metrics.height >> 6) + 1);
            }

            for(uint32_t row = 0; row < bmp->rows; ++row) {
                for(uint32_t col = 0; col < bmp->width; ++col) {
                    uint32_t x = pen_x + col;
                    uint32_t y = pen_y + row;
                    pixels[y * tex_width + x] = bmp->buffer[row * bmp->pitch + col];
                }
            }

            glyph[i].x0 = pen_x;
            glyph[i].y0 = pen_y;
            glyph[i].x1 = pen_x + bmp->width;
            glyph[i].y1 = pen_y + bmp->rows;

            //            glyph[i].x_offset = face->glyph->bitmap_left;
            //            glyph[i].y_offset = face->glyph->bitmap_top;
            //            glyph[i].advance_x = face->glyph->advance.x >> 6;
            //            glyph[i].advance_y = face->glyph->advance.y >> 6;

            pen_x += bmp->width + 1;
        }
    }

    void TextFt2::init(const Shader& txt_shader, const Ft2Font128& font)
    {
        shader = &txt_shader;
        font_size = font.height;
        glGenTextures(1, &obj_id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, obj_id);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, font.tex_width);
        glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, font.tex_width);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RED, font_size, font_size, 128, 0, GL_RED, GL_UNSIGNED_BYTE,
                     nullptr);
        log_gl_error_cmd();

        for(uint8_t i = 0; i < 128; ++i) {
            uint32_t char_w = font.glyph[i].x1 - font.glyph[i].x0;
            uint32_t char_h = font.glyph[i].y1 - font.glyph[i].y0;
            glTexSubImage3D(
                GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, char_w, char_h, 1, GL_RED, GL_UNSIGNED_BYTE,
                &font.pixels[font.glyph[i].y0 * font.tex_width + font.glyph[i].x0]);

            log_gl_error_cmd();
            //            log_warn_cmd("\nx_offset: %d\ny_offset: %d\nindex(0-128): %d\nwidth: %d\nheight: %d",
            //                         font.glyph[i].x_offset, font.glyph[i].y_offset, i, char_w,
            //                         char_h);
        }

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        log_gl_error_cmd();
        // Setting up buffers and attributes
        GLuint vbo;
        GLuint ebo;
        GLuint quad_vao;

        glGenVertexArrays(1, &quad_vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(quad_vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTICES_PER_QUAD, quad_vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (GLvoid*)(sizeof(math::vec2)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        log_gl_error_cmd();
    }

    void TextFt2::set_text(const char* text) {}

    void TextFt2::draw(const math::vec2& pos, const float rotation)
    {
        shader->run();
        math::mat4 model =
            math::transform(math::vec3(font_size, font_size, 1.0f), math::vec3(0.0f, 0.0f, 1.0f),
                            rotation, math::vec3(pos.x, pos.y, 0.0f));

        shader->set_mat4("model", model);
        shader->set_int("image_array", obj_id);
        log_gl_error_cmd();
        glActiveTexture(GL_TEXTURE0 + obj_id);
        log_gl_error_cmd();
        glBindTexture(GL_TEXTURE_2D_ARRAY, obj_id);
        log_gl_error_cmd();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        log_gl_error_cmd();
        //        glBindVertexArray(0);
    }
}