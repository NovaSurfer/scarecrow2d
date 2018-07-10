//
// Created by Maksim Ruts on 25-Apr-18.
//

#include "sprite.h"

Sprite::Sprite(const char *path, bool resizable = false)
{
    if(resizable)
        texture = TextureManager::load_texture(path);
    else std::tie(texture, surface) = TextureManager::load_texture_resizable(path);
}

void Sprite::init()
{
    transform = &entity->get_component<Transform>();

    srcrect.x = srcrect.y = 0;
    srcrect.w = srcrect.h = 28;
    destrect.w = destrect.h = 28;

    auto halfWidth = (int)(srcrect.w * 0.5f);
    center.x = halfWidth;
    center.y = srcrect.h - halfWidth;
};

void Sprite::update()
{
    // TODO: check if we have a transform component
    destrect.x = static_cast<int>(transform->get_position().x);
    destrect.y = static_cast<int>(transform->get_position().y);
    resize_surface();
}

void Sprite::draw()
{
    TextureManager::draw_texture(texture, srcrect, destrect, transform->get_rotation(), center, SDL_FLIP_NONE);
}

void Sprite::set_texture(const char *path)
{
    texture = TextureManager::load_texture(path);
}

void Sprite::resize_surface()
{
    if(surface != nullptr)
    {
        SDL_Rect destrect = transform->get_scale();
        SDL_BlitScaled(surface, nullptr, surface, &destrect);
    }
}
