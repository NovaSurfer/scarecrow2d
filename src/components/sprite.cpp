//
// Created by Maksim Ruts on 25-Apr-18.
//

#include "sprite.h"

Sprite::Sprite(std::string_view path)
{
    set_texture(path);
}

void Sprite::init()
{
    transform = &entity->get_component<Transform>();

    srcrect.x = srcrect.y = 0;
    srcrect.w = srcrect.h = 64;
    destrect.w = destrect.h = 64;

    calc_pivot();
};

void Sprite::update()
{
    destrect.x = static_cast<int>(transform->get_position().x);
    destrect.y = static_cast<int>(transform->get_position().y);
}

void Sprite::draw()
{
    TextureManager::draw_texture(texture, srcrect, destrect, transform->get_rotation(), pivot, SDL_FLIP_NONE);
}

void Sprite::set_texture(std::string_view path)
{
    texture  = TextureManager::load_texture(path);
}

void Sprite::resize(const SDL_Point dest_size)
{
   destrect.w += dest_size.x;
   destrect.h += dest_size.y;
   calc_pivot();
}

void Sprite::calc_pivot()
{
    auto halfWidth = (int)(destrect.w * 0.5f);
    pivot.x = halfWidth;
    pivot.y = destrect.h - halfWidth;
}
