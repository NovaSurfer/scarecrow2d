//
// Created by novasurfer on 12/31/19.
//

#ifndef SCARECROW2D_TEXT_FT2_H
#define SCARECROW2D_TEXT_FT2_H

#include "math/vector2.h"
#include "math/vector3.h"
#include "sc2dTypes.h"
#include "shader.h"
#include <freetype2/ft2build.h>
#include <map>
#include FT_FREETYPE_H

namespace sc2d
{

    /**
     *
     */
    struct GlyphInfo
    {
        // coords of glyph in texture atlas
        uint32_t x0;
        uint32_t y0;
        uint32_t x1;
        uint32_t y1;
        // left & top bearing
        uint32_t x_offset;
        uint32_t y_offset;
        // x advance
        uint32_t advance;
    };

    /**
     *
     */
    class Ft2Font128
    {
    public:
        void init(const char* font_path, uint8_t font_size);
        void destroy() const
        {
            FT_Done_FreeType(ft);
        }

        uint32_t tex_width;
        unsigned char* pixels;
        GlyphInfo glyph_data[128];
    private:
        FT_Library ft;
    };

    /*
     *
     */
    class TextFt2
    {
    public:
        void init(const Shader& txt_shader, const Ft2Font128& font);
        void set_text(const char* text);
        void draw(const math::vec2& pos, const float rotation);
        void destroy() const
        {
            glDeleteTextures(1, &obj_id);
        };

    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        GLuint obj_id;
        const Shader* shader;
    };
}
#endif //SCARECROW2D_TEXT_FT2_H
