//
// Created by Maksim Ruts on 17-Apr-18.
//

#ifndef INC_2D_ENGINE_TEXTUREMANAGER_H
#define INC_2D_ENGINE_TEXTUREMANAGER_H

#include "game.h"
#include "math/matrices.h"
#include <iostream>


class TextureManager {
public:
    static SDL_Texture *load_texture(const char *texFile);
    static std::pair<SDL_Texture *, SDL_Surface *> load_texture_resizable(const char *texFile);
    static void draw_texture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);
    static void draw_texture(SDL_Texture *texture, const SDL_Rect &srcrect, const SDL_Rect &destrect,
                             const double angle, const SDL_Point &center, const SDL_RendererFlip flip);

};


#endif //INC_2D_ENGINE_TEXTUREMANAGER_H
