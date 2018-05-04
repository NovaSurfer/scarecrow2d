//
// Created by Maksim Ruts on 25-Apr-18.
//

#include "transform.h"

void Transform::init()
{
    velocity.x = 0;
    velocity.y = 0;
}

void Transform::update()
{
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
}

