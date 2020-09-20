//
// Created by novasurfer on 9/6/20.
//

#ifndef SCARECROW2D_RENDERQUEUE_H
#define SCARECROW2D_RENDERQUEUE_H

#include "renderable.h"
#include <core/log2.h>
#include <vector>

namespace sc2d
{

    class RenderQueue
    {

        struct rendqitem_compare
        {
            // Priority: layer > shader_id > tex_id
            bool operator()(const rend_data2d* first, const rend_data2d* second)
            {
                const auto f_ls = first->layer + first->shader;
                const auto s_ls = second->layer + second->shader;

                if(first->layer > second->layer) {
                    return true;
                } else if(first->shader > second->shader && first->layer >= second->layer) {
                    return true;
                } else if(first->texid > second->texid && f_ls >= s_ls) {
                    return true;
                }
                return false;
            }
        };

    public:
        void draw();
        void pop();

        void push(const rend_data2d& item)
        {
            rendq.emplace_back(&item);
            if(rendq.size() > 1) {
                sort();
            }
        }

    private:
        void sort();
        std::vector<const rend_data2d*> rendq;
    };
}
#endif //SCARECROW2D_RENDERQUEUE_H
