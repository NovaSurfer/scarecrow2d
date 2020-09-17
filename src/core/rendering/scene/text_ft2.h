//
// Created by novasurfer on 12/31/19.
//

#ifndef SCARECROW2D_TEXT_FT2_H
#define SCARECROW2D_TEXT_FT2_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "core/rendering/renderable.h"
#include "core/rendering/rendering_types.h"
#include "core/rendering/shader.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include <map>
#include <string>

namespace sc2d
{
    static constexpr size_t ASCII_TABLE_SIZE = 128;
    static constexpr size_t ASCII_EXTENDED_TABLE_SIZE = 256;

    /**
     * Glyph data
     */
    struct GlyphInfo
    {
        // coords of glyph in texture atlas
        uint32_t x0;
        uint32_t y0;
        uint32_t x1;
        uint32_t y1;
        uint32_t advance_x;
        uint32_t bearing_x;
        uint32_t bearing_y;
    };

    /**
     * Contains font data
     */
    class Ft2Font
    {
    public:
        void init(const char* font_path, uint32_t font_size, uint32_t chars_table_size);
        void destroy() const
        {
            FT_Done_FreeType(ft);
        }

        uint32_t chars_table_lenght;
        uint32_t texture_width;
        uint32_t height; // font height (size)
        uint32_t ascender;
        unsigned char* pixels;
        // TODO: chars_table_size
        GlyphInfo glyph[128];

    private:
        FT_Library ft;
    };

    /*
     *
     */
    class TextFt2 : public obj2d_instatiable
    {
    public:
        void init(const Shader& txt_shader, const Ft2Font& font);
        void set_text(const char* text);
        const std::string& get_text() const
        {
            return text;
        }
        void set_pos(const math::vec2& pos, const float rotation);
        void draw();
        void destroy() const
        {
            glDeleteTextures(1, &texid);
        };

    private:
        const Ft2Font* font;
        std::string text;
    };
}
#endif //SCARECROW2D_TEXT_FT2_H
