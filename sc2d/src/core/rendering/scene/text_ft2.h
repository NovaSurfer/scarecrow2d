//
// Created by novasurfer on 12/31/19.
//

#ifndef SCARECROW2D_TEXT_FT2_H
#define SCARECROW2D_TEXT_FT2_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "base/types.h"
#include "core/rendering/renderable.h"
#include "core/rendering/rendering_types.h"
#include "core/rendering/shader.h"
#include "math/vector2.h"
#include "math/vector3.h"
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
        u32 x0;
        u32 y0;
        u32 x1;
        u32 y1;
        u32 advance_x;
        u32 bearing_x;
        u32 bearing_y;
    };

    /**
     * Contains font data
     */
    class Ft2Font128
    {
    public:
        void init(const char* font_path, u32 font_size);
        void destroy() const
        {
            FT_Done_FreeType(ft);
        }

        u32 texture_width;
        u32 height; // font height (size)
        u32 ascender;
        unsigned char* pixels;
        GlyphInfo glyph[ASCII_TABLE_SIZE];

    private:
        FT_Library ft;
    };

    /*
     *
     */
    class TextFt2 : public obj2d
    {
    public:
        void init(const Shader& txt_shader, const Ft2Font128& font);
        void set_text(const char* text);
        const std::string& get_text() const
        {
            return text;
        }
        void set_pos(const math::vec2& pos, float rotation);
        void draw();
        void destroy() const
        {
            glDeleteTextures(1, &texid);
        };

    private:
        const Ft2Font128* font;
        std::string text;
    };
}
#endif //SCARECROW2D_TEXT_FT2_H
