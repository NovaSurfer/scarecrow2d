//
// Created by max on 2/1/22.
//

#include "scene2d.h"
#include "core/rendering/renderable.h"
#include <algorithm>

namespace sc2d
{
    void Scene2d::add_object(sc2d::obj2d* object2d)
    {
        if(std::find(objects.begin(), objects.end(), object2d) != objects.end())
        {
            // duplicate, don't add
            return;
        }
        objects.push_back(object2d);
    }

    void Scene2d::remove_object(obj2d* object2d)
    {
        objects.erase(std::remove(objects.begin(), objects.end(), object2d), objects.end());
    }

    void Scene2d::update_object(obj2d* object2d)
    {

    }

    std::vector<obj2d*> Scene2d::find_childrens(const obj2d* object2d) const
    {
        std::vector<obj2d*> result;
        for(int i = 0, size = objects.size(); i < size; ++i) {
            if(objects[i] == nullptr || objects[i] == object2d) {
                continue;
            }

            obj2d* iterator = objects[i]->parent;
            if(iterator != nullptr)
            {
                if(iterator == object2d)
                {
                    result.push_back(objects[i]);
                    continue;
                }
                iterator = iterator->parent;
            }
        }
        return result;
    }

    obj2d* Scene2d::raycast(const math::ray2d& ray)
    {
        obj2d* result = nullptr;
        float result_f = -1.0f;

        for(int i = 0; i < objects.size(); ++i) {
            const math::vec2 pos = objects[i]->pos;
            const math::vec2 size = objects[i]->size;
            math::rect2d rect = math::rect2d::from_min_max(pos, size);

            // todo: incorrect, need to implement 2d raycast hit info
            float r = math::line_rect({ray.origin, ray.direction}, rect);
            if( (result == nullptr && r >= 0) || (result != nullptr && r < result_f) ) {
                result = objects[i];
                result_f = r;
            }
        }
        return result;
    }

    std::vector<obj2d*> Scene2d::query(const math::circle& circle)
    {

    }

    std::vector<obj2d*> Scene2d::query(const math::rect2d rect)
    {
    }

}