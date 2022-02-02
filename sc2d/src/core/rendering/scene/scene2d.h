//
// Created by max on 2/1/22.
//

#ifndef SCARECROW2D_SCENE2D_H
#define SCARECROW2D_SCENE2D_H

#include <vector>
#include "math/geometry2d.h"

namespace sc2d
{

    struct obj2d;
    class Scene2d
    {
    public:
        void add_object(obj2d* object2d);

        void remove_object(obj2d* object2d);

        void update_object(obj2d* object2d);

        std::vector<obj2d*> find_childrens(const obj2d* object2d) const;

        obj2d* raycast(const math::ray2d& ray);

        std::vector<obj2d*> query(const math::circle& circle);

        std::vector<obj2d*> query(const math::rect2d rect);

    private:
        std::vector<obj2d*> objects;
    };
}

#endif //SCARECROW2D_SCENE2D_H
