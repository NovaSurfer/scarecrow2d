//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_POSITION_H
#define INC_2D_ENGINE_POSITION_H

#include "../math/matrices.h"
#include "../math/vector.h"
#include "components.h"

class Transform : public Component
{
public:
    Transform()
        : position(math::vec2())
        , scale(SDL_Point{})
        , angle(0){};
    Transform(math::vec2 position, SDL_Point scale, double angle);

    math::vec2 const& get_position() const
    {
        return position;
    }
    double const& get_rotation() const
    {
        return angle;
    }
    SDL_Point get_scale() const
    {
        return scale;
    }
    void set_pos_x(const float x);
    void set_pos_y(const float y);
    void set_scale(const SDL_Point scale);
    void rotate(const double angle);

private:
    SDL_Point scale;
    math::vec2 position;
    double angle;
};

#endif //INC_2D_ENGINE_POSITION_H
