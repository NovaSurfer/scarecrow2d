//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_POSITION_H
#define INC_2D_ENGINE_POSITION_H

#include "components.h"
#include "../math/vector.h"
#include "../math/matrices.h"

class Transform : public Component {
public:
    Transform() : position(math::vec2()), scale(math::mat2()), angle(0) {};
    Transform(math::vec2 position, math::mat2 scale, double angle);

    math::vec2 const &get_position() const { return position; }
    double const &get_rotation() const { return angle; }
    SDL_Rect get_scale() const;
    void set_pos_x(const float x);
    void set_pos_y(const float y);
    void set_scale(const math::mat2& scale);
    void rotate(const double angle);

private:
    math::mat2 scale;
    math::vec2 position;
    double angle;

};

#endif //INC_2D_ENGINE_POSITION_H
