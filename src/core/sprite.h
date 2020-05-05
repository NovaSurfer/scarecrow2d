//
// Created by novasurfer on 20.12.18.
//

#ifndef INC_2D_GAME_SPRITE_H
#define INC_2D_GAME_SPRITE_H

#include "renderable.h"

namespace sc2d
{

    class Sprite : public obj2d
    {
    public:
        void init(const Shader& shader);
        void draw();
    private:
        GLuint quad_vao;
    };
}

#endif //INC_2D_GAME_SPRITE_H
