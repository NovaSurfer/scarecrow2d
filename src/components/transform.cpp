//
// Created by Maksim Ruts on 25-Apr-18.
//

#include "transform.h"

Transform::Transform(math::vec2 position, SDL_Point scale, double angle)
        : position(position), scale(scale), angle(angle) { }

void Transform::set_pos_x(const float x)
{
    this->position.x += x;
}

void Transform::set_pos_y(const float y)
{
    this->position.y += y;
}

void Transform::set_scale(const SDL_Point scale)
{
    this->scale.x += scale.x;
    this->scale.y += scale.y;
    Sprite *sprite = &entity->get_component<Sprite>();
    sprite->resize(this->scale);
}

void Transform::rotate(const double angle)
{
    this->angle += angle;
    if(this->angle > 360)
        this->angle = 0;
    if(this->angle < 0)
        this->angle = 360;
}