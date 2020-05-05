//
// Created by novasurfer on 12/31/19.
//

#ifndef SCARECROW2D_TEXT_FT2_H
#define SCARECROW2D_TEXT_FT2_H

#include "math/vector2.h"
#include "math/vector3.h"
#include "rendering_types.h"
#include "shader.h"
#include <freetype2/ft2build.h>
#include <map>
#include <string>
#include FT_FREETYPE_H

namespace sc2d
{
    static const size_t ASCII_TABLE_SIZE = 128;
    static const size_t ASCII_EXTENDED_TABLE_SIZE = 256;

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
     *
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
    class TextFt2
    {
    public:
        void init(const Shader& txt_shader, const Ft2Font& font);
        void set_text(const char* text);
        [[nodiscard]] const std::string& get_text() const
        {
            return text;
        }
        void set_pos(const math::vec2& pos, const float rotation);
        void draw();
        void destroy() const
        {
            glDeleteTextures(1, &obj_id);
        };

    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        uint32_t lenght = 0;
        GLuint obj_id;
        GLuint quad_vao;
        const Shader* shader;
        const Ft2Font* font;
        std::string text;
    };
}
#endif //SCARECROW2D_TEXT_FT2_H
