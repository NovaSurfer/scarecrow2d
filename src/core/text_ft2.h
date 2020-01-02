//
// Created by novasurfer on 12/31/19.
//

#ifndef SCARECROW2D_TEXT_FT2_H
#define SCARECROW2D_TEXT_FT2_H

#include "sc2dTypes.h"
#include "shader.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include <freetype2/ft2build.h>
#include <map>
#include FT_FREETYPE_H

namespace sc2d
{

    constexpr const uint32_t MAX_WIDTH = 1024;

    class Text_ft2
    {
    public:
        void init(const Shader& shader, const char* font_path, uint8_t fount_size);
        void destroy() const { FT_Done_FreeType(ft); };
        void draw();

        uint8_t font_size;
    private:

        struct character_info {
            float ax; // advance.x
            float ay; // advance.y

            float bw; // bitmap.width;
            float bh; // bitmap.rows;

            float bl; // bitmap_left;
            float bt; // bitmap_top;

            float tx; // x offset of glyph in texture coordinates
            float ty;
        } c[128];

        static Vertex quad_vertices[VERTICES_PER_QUAD];

        uint32_t width = 0; // width of texture in pixels
        uint32_t height = 0; // height of texture in pixels
        GLuint obj_id;
        const Shader* shader;
        FT_Library ft;
    };
}
#endif //SCARECROW2D_TEXT_FT2_H
