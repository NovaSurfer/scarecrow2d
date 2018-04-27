//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_POSITION_H
#define INC_2D_ENGINE_POSITION_H

#include "components.h"

class Transform : public Component
{
private:
    int xpos = 0;
    int ypos = 0;
public:
    Transform() = default;
    Transform(int x, int y) : xpos(x), ypos(y) {};

    inline int x() const {return xpos;}
    inline int y() const {return ypos;}

    void init() override;
    void update() override;
    void setPos(int x, int y);

};

#endif //INC_2D_ENGINE_POSITION_H
