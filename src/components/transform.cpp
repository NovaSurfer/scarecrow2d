//
// Created by Maksim Ruts on 25-Apr-18.
//

#include "transform.h"

Transform::Transform(math::vec2 position, math::mat2 scale, double angle)
        : position(position), scale(scale), angle(angle) { }

void Transform::set_pos_x(const float x)
{
    this->position.x += x;
}

void Transform::set_pos_y(const float y)
{
    this->position.y += y;
}

void Transform::set_scale(const math::mat2 &scale)
{
    this->scale += scale;
}

void Transform::rotate(const double angle)
{
    this->angle += angle;
    if(this->angle > 360)
        this->angle = 0;
    if(this->angle < 0)
        this->angle = 360;

    std::cout << this->angle << '\n';
}

SDL_Rect Transform::get_scale() const
{
    SDL_Rect stretchRect;
    stretchRect.x = static_cast<int>(scale.n[0][0]);
    stretchRect.y = static_cast<int>(scale.n[0][1]);
    stretchRect.w = static_cast<int>(scale.n[1][0]);
    stretchRect.h = static_cast<int>(scale.n[1][1]);
    return stretchRect;
}

/*

math::mat2 Transform::rotation(float pitch)
{
    return x_rotation(pitch);
}

math::mat2 Transform::x_rotation(float angle)
{
    angle = math::utils::deg2rag(angle);
    return math::mat2( cosf(angle),  sinf(angle),
                      -sinf(angle),  cosf(angle) );
}

void Transform::scaling()
{
//    SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
}
*/