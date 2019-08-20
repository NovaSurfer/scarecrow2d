//
// Created by novasurfer on 7/7/19.
//

#ifndef INC_2D_GAME_SPRITE_SHEET_H
#define INC_2D_GAME_SPRITE_SHEET_H

#include "math/size2d.h"
#include "math/vector2.h"
#include "sc2dTypes.h"
#include "shader.h"
#include <vector>

namespace sc2d
{
    class TextureAtlas;

    class SpriteSheet
    {
    public:
        SpriteSheet() = default;
        SpriteSheet(const Shader& shader, const math::size2d& size, std::vector<math::vec2>&& pos,
                    std::vector<uint32_t>&& gid);
        void draw(const TextureAtlas& texatlas);

    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        Shader shader;
        math::size2d size;
        std::vector<math::vec2> positions;
        std::vector<uint32_t> gids;
        GLuint quad_vao;

        void init_data();
    };
}

#endif //INC_2D_GAME_SPRITE_SHEET_H
