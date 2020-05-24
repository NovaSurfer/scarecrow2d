//
// Created by novasurfer on 20.12.18.
//

#ifndef INC_2D_GAME_SPRITE_H
#define INC_2D_GAME_SPRITE_H

#include "renderable.h"

namespace sc2d
{

    struct Sprite : public obj2d
    {
        void init(const Shader& shader);
        void draw();
    };
}

#endif //INC_2D_GAME_SPRITE_H
