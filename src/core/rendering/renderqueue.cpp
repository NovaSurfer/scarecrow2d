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
        for(const rend_data2d* i : rendq) {
            i->shader.run();
            glActiveTexture(GL_TEXTURE0 + i->texid);
            glBindVertexArray(i->quad_vao);
            if(i->instances_count == 0) {
                glBindTexture(GL_TEXTURE_2D, i->texid);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            } else {
                glBindTexture(GL_TEXTURE_2D_ARRAY, i->texid);
                glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr,
                                        i->instances_count);
            }
        }
    }

}