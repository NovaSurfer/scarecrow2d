//
// Created by novasurfer on 9/6/20.
//

#include "renderqueue.h"
#include <algorithm>

namespace sc2d
{
    void sc2d::RenderQueue::pop()
    {
        rendq.pop_back();
    }

    void sc2d::RenderQueue::sort()
    {
        std::stable_sort(rendq.begin(), rendq.end(), rendqitem_compare());
    }

    // TODO: check for the same shader & texture ids
    void sc2d::RenderQueue::draw()
    {
        for(const rendq_item& i : rendq) {
            i.renddata->shader.run();
            glActiveTexture(GL_TEXTURE0 + i.renddata->texid);
            glBindVertexArray(i.renddata->quad_vao);
            if(i.instances_count == 0) {
                glBindTexture(GL_TEXTURE_2D, i.renddata->texid);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            } else {
                glBindTexture(GL_TEXTURE_2D_ARRAY, i.renddata->texid);
                glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr,
                                        i.instances_count);
            }
        }
    }

}