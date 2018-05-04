//
// Created by Maksim Ruts on 17-Apr-18.
//

#include "gameObject.h"

GameObject::GameObject(const char *textureSheet, int x, int y) : xpos(x), ypos(y)
{
    objTexture = TextureManager::load_texture(textureSheet);
}

void GameObject::update()
{

    xpos++;
    ypos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

