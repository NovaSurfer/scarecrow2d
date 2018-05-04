//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_POSITION_H
#define INC_2D_ENGINE_POSITION_H

#include "components.h"
#include "../math/vector.h"

struct Transform : public Component
{
    math::vec2 position;
    math::vec2 velocity;

    int speed = 3;

    Transform() : position(math::vec2()) {};

    explicit Transform(math::vec2 position) : position(position) {};

    void init() override;
    void update() override;
};

#endif //INC_2D_ENGINE_POSITION_H
