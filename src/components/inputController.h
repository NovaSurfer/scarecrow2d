//
// Created by maksim on 4/29/18.
//

#ifndef INC_2D_ENGINE_INPUTCONTROLLER_H
#define INC_2D_ENGINE_INPUTCONTROLLER_H

#include "../game.h"
#include "components.h"

class InputController : public Component {
public:
    Transform *transform;

    void init() override;

    void update() override;

private:
};


#endif //INC_2D_ENGINE_INPUTCONTROLLER_H
