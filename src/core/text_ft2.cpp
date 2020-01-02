//
// Created by novasurfer on 12/31/19.
//

#include "text_ft2.h"
#include "debug_utils.h"
#include "log2.h"
#include "math/utils.h"

namespace sc2d
{
    void Text_ft2::init(const sc2d::Shader& shader, const char* font_path, uint8_t font_size)
    {
        memset(c, 0, sizeof c);

        if(FT_Init_FreeType(&ft))
            log_err_cmd("CAN NOT INIT FREETYPE.");

        FT_Face face;
        this->font_size = font_size;

        if(FT_New_Face(ft, font_path, 0, &face))
            log_info_cmd("FAILED TO LOAD FONT.");

        FT_Set_Pixel_Sizes(face, 0, font_size);

        if(FT_Load_Char(face, 'F', FT_LOAD_RENDER))
            log_err_cmd("FREETYPE :: Failed to load Glyph");

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        FT_GlyphSlot glyph = face->glyph;
        uint32_t row_width = 0;
        uint32_t row_height = 0;

        for(unsigned char i = 32; i < 128; ++i) {
            // Load character glyph
            if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
                log_warn_cmd("Failed to load glyph at index: %d.", i);
                continue;
            }
            if(row_width + glyph->bitmap.width + 1 >= MAX_WIDTH) {
                width = math::utils::max(width, row_width);
                height += row_width;
                row_height = 0;
                row_width = 0;
            }
            row_width += glyph->bitmap.width;
            row_height = math::utils::max(row_height, glyph->bitmap.rows);
        }

        width = math::utils::max(width, row_width);
        height += row_height;

        // Create a texture that will be used to hold all ASCII glyphs
        glGenTextures(1, &obj_id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, obj_id);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RED, width, height, 128, 0, GL_RED,
                     GL_UNSIGNED_BYTE, nullptr);
        log_gl_error_cmd();

        // Enabling clamping to edge to prevent artifacts when scaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Paste all glyph bitmaps into the texture, remembering the offset
        uint32_t x_offset = 0;
        uint32_t y_offset = 0;

        row_height = 0;

        log_gl_error_cmd();
        for(int i = 32; i < 128; i++) {
            if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
                log_warn_cmd("Failed to load glyph at index: %d.", i);
                continue;
            }

            if(x_offset + glyph->bitmap.width + 1 >= MAX_WIDTH) {
                y_offset += row_height;
                row_height = 0;
                x_offset = 0;
            }

            // WIP
            log_warn_cmd("\nx_offset: %d\ny_offset: %d\nglyph_width: %d\nglyph_rows: %d", x_offset,
                         y_offset, glyph->bitmap.width, glyph->bitmap.rows);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, x_offset, y_offset, i, glyph->bitmap.width,
                            glyph->bitmap.rows, 1, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
            log_gl_error_cmd();

            c[i].ax = glyph->advance.x >> 6;
            c[i].ay = glyph->advance.y >> 6;

            c[i].bw = glyph->bitmap.width;
            c[i].bh = glyph->bitmap.rows;

            c[i].bl = glyph->bitmap_left;
            c[i].bt = glyph->bitmap_top;

            c[i].tx = x_offset / (float)width;
            c[i].ty = y_offset / (float)height;

            row_height = math::utils::max(row_height, glyph->bitmap.rows);
            x_offset += glyph->bitmap.width + 1;
        }

        log_info_cmd("Generated a %d x %d (%d kb) texture atlas\n", width, height,
                     width * height / 1024);
    }
}