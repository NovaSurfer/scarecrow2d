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
    } else {
        std::cout << " :: ERROR :: TEXTURE_LOADING :: " << IMG_GetError() << std::endl;
        return nullptr;
    }
}

std::pair<SDL_Texture*, SDL_Surface*>
TextureManager::load_texture_resizable(const char *texFile)
{
    SDL_Surface *tmpSurface = IMG_Load(texFile);
    if (tmpSurface)
    {
        SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        return std::make_pair(tex, tmpSurface);
    } else {
        std::cout << " :: ERROR :: TEXTURE_LOADING :: " << IMG_GetError() << std::endl;
        return {};
    }
}

void TextureManager::draw_texture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

void TextureManager::draw_texture
(SDL_Texture *texture, const SDL_Rect &srcrect, const SDL_Rect &destrect, const double angle, const SDL_Point &center,
 const  SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &srcrect, &destrect, angle, &center, flip);
}
