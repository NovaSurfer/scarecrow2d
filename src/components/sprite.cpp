//
// Created by Maksim Ruts on 25-Apr-18.
//

#include "sprite.h"

Sprite::Sprite(const char *path)
{
    texture = TextureManager::load_texture(path);
}

void Sprite::init()
{
    transform = &entity->get_component<Transform>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 28;
    destRect.w = destRect.h = 28;
}

void Sprite::update()
{
    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);
}

void Sprite::draw()
{
    TextureManager::draw_texture(texture, srcRect, destRect);
}

void Sprite::set_texture(const char *path)
{
    texture = TextureManager::load_texture(path);
}
