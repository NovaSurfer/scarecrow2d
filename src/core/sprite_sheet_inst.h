//
// Created by novasurfer on 7/7/19.
//

#ifndef INC_2D_GAME_SPRITE_SHEET_INST_H
#define INC_2D_GAME_SPRITE_SHEET_INST_H

#include "core/dbg/ogl_errors.h"
#include "math/transform.h"
#include "math/vector2.h"
#include "renderable.h"
#include "rendering_types.h"
#include "shader.h"
#include "types.h"
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
        SpriteSheetInstData(const u32* const gids, const math::vec2* const positions)
            : gid {gids}
            , pos {positions}
        { }

        const u32* const gid = nullptr;
        const math::vec2* const pos = nullptr;
    };

    struct SpriteSheetInstanced : obj2d_instatiable
    {
        SpriteSheetInstanced() = default;
        /**
         * Initialize data
         * @param spr_shader shader
         * @param spr_size tile size
         * @param spr_count number of sprites
         * @param sid reference to sprite sheet instance data
         */
        void init(const Shader& spr_shader, const math::vec2& size, const size_t spr_count,
                  const SpriteSheetInstData& sid);
        void draw() const;
    };
}

#endif //INC_2D_GAME_SPRITE_SHEET_INST_H
