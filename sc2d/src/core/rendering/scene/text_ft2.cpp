//
// Created by novasurfer on 12/31/19.
//

#include "text_ft2.h"
#include "core/dbg/dbg_asserts.h"
#include "core/log2.h"
#include "math/utils.h"
#include <math/transform.h>
#include <vector>

namespace sc2d
{

    void Ft2Font128::init(const char* font_path, u32 font_size)
    {
        height = font_size;

        DBG_RETURN_IF(FT_Init_FreeType(&ft), "can't init FreeType");

        FT_Face face;

        DBG_RETURN_IF(FT_New_Face(ft, font_path, 0, &face), "failed to load font");

        FT_Set_Pixel_Sizes(face, 0, font_size);

        // quick and dirty max texture size estimate
        texture_width = 1;
        u32 max_dim = (1 + (face->size->metrics.height >> 6)) * ceilf(sqrtf(ASCII_TABLE_SIZE));
        while(texture_width < max_dim)
            texture_width <<= 1;
        u32 tex_height = texture_width;

        // render glyphs to atlas
        pixels = (unsigned char*)calloc(texture_width * tex_height, 1);
        ascender = face->ascender >> 5;
        u32 pen_x = 0, pen_y = 0;

        for(size_t i = 32; i < ASCII_TABLE_SIZE; ++i) {
            // Maybe its better to use FL_LOAD_TARGET_LIGHT for regular, non-pixelart fonts.
            FT_Load_Char(face, i, FT_LOAD_RENDER);
            FT_Bitmap* bmp = &face->glyph->bitmap;

            if(pen_x + bmp->width >= texture_width) {
                pen_x = 0;
                pen_y += ((face->size->metrics.height >> 6) + 1);
            }

            for(u32 row = 0; row < bmp->rows; ++row) {
                for(u32 col = 0; col < bmp->width; ++col) {
                    u32 x = pen_x + col;
                    u32 y = pen_y + row;
                    pixels[y * texture_width + x] = bmp->buffer[row * bmp->pitch + col];
                }
            }

            glyph[i].x0 = pen_x;
            glyph[i].y0 = pen_y;
            glyph[i].x1 = pen_x + bmp->width;
            glyph[i].y1 = pen_y + bmp->rows;

            glyph[i].advance_x = face->glyph->advance.x >> 6;
            glyph[i].bearing_x = face->glyph->metrics.horiBearingX >> 6;
            glyph[i].bearing_y = face->glyph->metrics.horiBearingY >> 6;

            pen_x += bmp->width + 1;
        }
    }

    void TextFt2::init(const Shader& txt_shader, const Ft2Font128& fnt)
    {
        shader = txt_shader;
        font = &fnt;

        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texid);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, font->texture_width);
        glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, font->texture_width);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RED, font->height, font->height,
                     ASCII_TABLE_SIZE, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

        for(u8 i = 0; i < ASCII_TABLE_SIZE; ++i) {
            u32 char_w = font->glyph[i].x1 - font->glyph[i].x0;
            u32 char_h = font->glyph[i].y1 - font->glyph[i].y0;
            glTexSubImage3D(
                GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, char_w, char_h, 1, GL_RED, GL_UNSIGNED_BYTE,
                &font->pixels[font->glyph[i].y0 * font->texture_width + font->glyph[i].x0]);
        }

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Setting up buffers and attributes
        GLuint vbo;
        GLuint ebo;

        glGenVertexArrays(1, &quad_vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(quad_vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTICES_PER_QUAD, QUAD_VERTICES,
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

    }

    void TextFt2::set_text(const char* txt)
    {
        const size_t chars_num = strlen(txt);
        if(!chars_num) {
            log_warn_cmd("Setting empty string.");
            return;
        }

        instances_count = chars_num;
        text = txt;
    }

    void TextFt2::set_pos(const math::vec2& pos, const float rotation)
    {
        if(!instances_count) {
            log_warn_cmd("Setting position to an empty text!");
            return;
        }

        std::vector<u32> char_indices(instances_count);
        std::vector<math::mat4> model_matrices(instances_count);
        std::vector<math::vec3> poss(instances_count);
        GLuint glyph_vbo;
        GLuint model_vbo;
        size_t i = 1;
        const auto* txt_chars = (const u8*)text.c_str();

        // Setting up position for the first character in text.
        float prev_x = pos.x;
        char_indices[0] = *txt_chars;
        // (Xpos + glyph_advance_x + glyph_bearing_x ; Ypos - glyph_bearing_y + font_face_ascender)
        poss[0] = math::vec3(pos.x, pos.y - font->glyph[*txt_chars].bearing_y + font->ascender, 0.f);
        model_matrices[0] = math::transform(math::vec3(48, 48, 1.0f), math::vec3(0.f, 0.f, 1.0f),
                                            rotation, poss[0]);

        // Setting up position for the rest characters.
        for(const auto* ch = txt_chars + 1; i < instances_count; ++ch, ++i) {
            u32 curr_char = *ch;
            u32 prev_char = *(ch - 1);
            u32 ascender = font->ascender;
            u32 advance_x = font->glyph[prev_char].advance_x;
            u32 bearing_x = font->glyph[prev_char].bearing_x;
            u32 bearing_y = font->glyph[curr_char].bearing_y;

            char_indices[i] = curr_char;
            poss[i] = math::vec3(prev_x + advance_x + bearing_x, pos.y - bearing_y + ascender, 0.f);
            prev_x += advance_x + bearing_x;
            model_matrices[i] = math::transform(math::vec3(font->height, font->height, 1.0f),
                                                math::vec3(0.0f, 0.0f, 1.0f), rotation, poss[i]);
        }

        // setting 'l_glyphid' attribute located in 'glyph_vbo' buffer
        glGenBuffers(1, &glyph_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, glyph_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(u32) * instances_count, char_indices.data(), GL_STATIC_DRAW);
        glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(u32), (GLvoid*)nullptr);
        glEnableVertexAttribArray(2);
        glVertexAttribDivisor(2, 1);

        // setting 'l_model' attribute, located in 'model_vbo' buffer
        glGenBuffers(1, &model_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, model_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(math::mat4) * instances_count, model_matrices.data(), GL_STATIC_DRAW);

        // FIXME: copied from "sprite_sheet_inst.cpp : 67"
        size_t matrow_size = sizeof(float) * 4;
        for(size_t j = 0; j < instances_count; ++j) {
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size, (GLvoid*)nullptr);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size,
                                  (GLvoid*)(matrow_size));
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size,
                                  (GLvoid*)(2 * matrow_size));
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size,
                                  (GLvoid*)(3 * matrow_size));

            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);
            glEnableVertexAttribArray(5);
            glEnableVertexAttribArray(6);

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);
        }
    }

    void TextFt2::draw()
    {
        shader.run();
        glActiveTexture(GL_TEXTURE0 + texid);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texid);
        glBindVertexArray(quad_vao);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, instances_count);
    }
}