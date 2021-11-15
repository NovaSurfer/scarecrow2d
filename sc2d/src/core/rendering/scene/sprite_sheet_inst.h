//
// Created by novasurfer on 7/7/19.
//

#ifndef INC_2D_GAME_SPRITE_SHEET_INST_H
#define INC_2D_GAME_SPRITE_SHEET_INST_H

#include "core/dbg/ogl_errors.h"
#include "core/rendering/renderable.h"
#include "core/rendering/rendering_types.h"
#include "core/rendering/shader.h"
#include "core/types.h"
#include "math/transform.h"
#include "math/vector2.h"
#include <vector>
#include "collections/arr.h"

namespace sc2d
{
    /**
     * Sprite sheet instance data
     */
    struct SpriteSheetInstData
    {
        arr<u32, limits::SPRITE_INSTANCES> gid;
        arr<math::vec2, limits::SPRITE_INSTANCES> pos;
    };

    struct SpriteSheetInstanced : obj2d
    {
        /**
         * Initialize data
         * @param spr_shader shader
         * @param spr_size tile size
         * @param spr_count number of sprites
         * @param sid reference to sprite sheet instance data
         */
        void init(const Shader& spr_shader, const math::vec2& size, const size_t spr_count,
                  const math::mat4& projection, const SpriteSheetInstData& sid);
        void draw() const;
    };
}

#endif //INC_2D_GAME_SPRITE_SHEET_INST_H
