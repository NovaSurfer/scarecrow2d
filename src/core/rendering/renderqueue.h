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
        struct rendq_item
        {
            rend_data2d* renddata;
            size_t instances_count;
        };

        struct rendqitem_compare
        {
            // Priority: layer > shader_id > tex_id
            bool operator()(const rendq_item& first, const rendq_item& second)
            {
                const auto f_ls = first.renddata->layer + first.renddata->shader;
                const auto s_ls = second.renddata->layer + second.renddata->shader;

                if(first.renddata->layer > second.renddata->layer) {
                    return true;
                } else if(first.renddata->shader > second.renddata->shader &&
                          first.renddata->layer >= second.renddata->layer) {
                    return true;
                } else if(first.renddata->texid > second.renddata->texid && f_ls >= s_ls) {
                    return true;
                }
                return false;
            }
        };

    public:
        void draw();
        void pop();

        template <typename T>
        void push(T& item)
        {
            rendq_item rendqitem;

            if constexpr(std::is_base_of_v<obj2d, T>) {
                rendqitem.renddata = static_cast<rend_data2d*>(&item);
                rendqitem.instances_count = 0;
            } else if constexpr(std::is_base_of_v<obj2d_instatiable, T>) {
                rendqitem.renddata = static_cast<rend_data2d*>(&item);
                rendqitem.instances_count = item.instances_count;
            }

            rendq.emplace_back(rendqitem);
            if(rendq.size() > 1) {
                sort();
            }
        }

    private:
        void sort();
        std::vector<rendq_item> rendq;
    };
}
#endif //SCARECROW2D_RENDERQUEUE_H
