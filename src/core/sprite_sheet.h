//
// Created by novasurfer on 7/7/19.
//

#ifndef INC_2D_GAME_SPRITE_SHEET_H
#define INC_2D_GAME_SPRITE_SHEET_H

#include "math/size2d.h"
#include "math/vector2.h"
#include "sc2dTypes.h"
#include "shader.h"

namespace sc2d
{
    class TextureAtlas;

    class SpriteSheet
    {
    public:
        SpriteSheet(const Shader& shader, const math::vec2& pos);
        void draw(const TextureAtlas& texatlas, const math::size2d& size,
                  const float rotate = 0.0f);

    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        Shader shader;
        math::vec2 position;
        GLuint quad_vao;

        void init_data();
    };
}

#endif //INC_2D_GAME_SPRITE_SHEET_H
