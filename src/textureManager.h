//
// Created by Maksim Ruts on 17-Apr-18.
//

#ifndef INC_2D_ENGINE_TEXTUREMANAGER_H
#define INC_2D_ENGINE_TEXTUREMANAGER_H

#include "game.h"
#include <iostream>


class TextureManager {
public:
    static SDL_Texture *load_texture(const char *texFile);

    static void draw_texture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);
};


#endif //INC_2D_ENGINE_TEXTUREMANAGER_H
