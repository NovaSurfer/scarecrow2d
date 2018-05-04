//
// Created by Maksim Ruts on 17-Apr-18.
//

#include "textureManager.h"

SDL_Texture *TextureManager::load_texture(const char *texFile)
{
    SDL_Surface *tmpSurface = IMG_Load(texFile);
    if (tmpSurface)
    {
        SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
        return tex;
    } else
    {
        std::cout << " :: ERROR :: TEXTURE_LOADING :: " << IMG_GetError() << std::endl;
        return nullptr;
    }
}

void TextureManager::draw_texture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
