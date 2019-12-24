//
// Created by novasurfer on 7/7/19.
//

#ifndef INC_2D_GAME_SPRITE_SHEET_INST_H
#define INC_2D_GAME_SPRITE_SHEET_INST_H

#include "debug_utils.h"
#include "math/size2d.h"
#include "math/transform.h"
#include "math/vector2.h"
#include "sc2dTypes.h"
#include "shader.h"
#include <vector>

namespace sc2d
{
    /**
     * Sprite sheet instance data
     */
    struct SpriteSheetInstData
    {
        /**
         * @param gids array of global map IDs
         * @param positions array of positions
         */
        SpriteSheetInstData(const uint32_t* const gids, const math::vec2* const positions)
            : gid {gids}
            , pos {positions}
        {}

        const uint32_t* const gid = nullptr;
        const math::vec2* const pos = nullptr;
    };

    class SpriteSheetInstanced
    {
    public:
        SpriteSheetInstanced() = default;
        /**
         * Initialize data
         * @param spr_shader shader
         * @param spr_size tile size
         * @param spr_count number of sprites
         * @param sid reference to sprite sheet instance data
         */
        void init_data(const sc2d::Shader& spr_shader, const math::size2d& spr_size,
                       const size_t spr_count, const SpriteSheetInstData& sid);
        /**
         * @param tex_id texture id (name)
         */
        void draw(const GLuint tex_id) const;

    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        const Shader* shader;
        size_t sprites_count;
    };
}

#endif //INC_2D_GAME_SPRITE_SHEET_INST_H
