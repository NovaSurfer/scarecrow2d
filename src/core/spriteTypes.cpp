//
// Created by novasurfer on 23.12.18.
//

#include "spriteTypes.h"

namespace sc2d {
     Quad SpriteTypes::SPRITE_QUAD
            {
                //positions      //tex coords  //colors (RGBA)
                {{ 0.5f,  0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0}},  // top right
                {{ 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0}},  // bottom right
                {{-0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0}},  // bottom left
                {{-0.5f,  0.5f}, {1.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0}},  // top left
            };

}